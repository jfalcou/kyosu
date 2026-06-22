//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/details/cayleyify.hpp>
#include <kyosu/functions/is_nan.hpp>
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/constants.hpp>
#include <iostream>
namespace kyosu
{
  template<typename Options>
  struct exp_t : eve::elementwise_callable<exp_t, Options, radpi_option, raw_option, pedantic_option, real_only_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z>  operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(exp_t, exp_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var exp
  //!   @brief Computes the exponential of the argument.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <kyosu/functions.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace kyosu
  //!   {
  //!      //regular call
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T exp(T z) noexcept;
  //!
  //!      // Semantic modifyiers
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T exp[raw}(T z) noexcept;
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T exp[radpi}(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     1. For complex inputs, returns the exponential following IEEE standards :
  //!
  //!       1. for every z: `exp(conj(z)) == conj(exp(z))`
  //!       2. If z is \f$\pm0\f$, the result is \f$1\f$
  //!       3. If z is \f$x+i \infty\f$ (for any finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
  //!       4. If z is \f$x+i \textrm{NaN}\f$ (for any finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
  //!       5. If z is \f$+\infty+i 0\f$, the result is \f$+\infty\f$
  //!       6. If z is \f$-\infty+i y\f$ (for any finite y), the result is \f$+0 e^{iy}\f$.
  //!       7. If z is \f$+\infty+i y\f$ (for any finite nonzero y), the result is \f$+\infty e^{iy}\f$.
  //!       8. If z is \f$-\infty+i \infty\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified)
  //!       9. If z is \f$+\infty+i \pm\infty\f$, the result is \f$\pm \infty+i \textrm{NaN}\f$ (the sign of the real part is unspecified).
  //!       10. If z is \f$-\infty+i \textrm{NaN}\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified).
  //!       11. If z is \f$\pm\infty+i \textrm{NaN}\f$, the result is \f$\pm \infty+i \textrm{NaN}\f$ (the sign of the real part is unspecified).
  //!       12. If z is \f$\textrm{NaN}\f$, the result is \f$\textrm{NaN}\f$.
  //!       13. If z is \f$\textrm{NaN}+i y\f$ (for any nonzero y), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
  //!       14. If z is \f$\textrm{NaN}+i \textrm{NaN}\f$, the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
  //!
  //!       For general cayley-dickson inputs, returns \f$e^{z_0}(\cos|\underline{z}|+\underline{z}\; \mathop{sinc}|\underline{z}|)\f$
  //!
  //!     2. with the raw options, no care is taken to satisfy the corners cases.
  //!     3. computes \f$ e^{\pi z}\f$. `exppi` alias can be used.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/exp.cpp}
  //======================================================================================================================
  inline constexpr auto exp = eve::functor<exp_t>;
  inline constexpr auto exppi = exp[radpi];
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{

  template<typename Z>
  KYOSU_FORCEINLINE  constexpr auto corners(const Z & z, Z rr) noexcept
  {
    auto [rz, iz] = z;
    rr = if_else(eve::is_pinf(iz),
                 if_else(eve::is_pinf(rz), Z(rz, eve::nan(as(rz))), if_else(eve::is_minf(rz), zero(as(rr)), rr)), rr);
    rr = if_else(eve::is_nan(iz), if_else(eve::is_minf(rz), zero, if_else(eve::is_pinf(rz), z, fnan(as(rr)))), rr);
    return if_else(eve::is_eqz(iz), Z(real(rr)), rr);
  }


  template<typename Z, eve::callable_options O>
  constexpr auto exp_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (concepts::real<Z>)
    {
      if constexpr (O::contains(real_only))
      {
        if constexpr (O::contains(radpi)) return eve::exp(eve::pi(eve::as(z))*z);
        else return eve::exp(z);
      }
      else
        return complex(exp[kyosu::real_only][o](z));
    }
    else if constexpr (concepts::complex<Z>)
    {
      if constexpr(O::contains(raw))
      {
        auto [rz, iz] = z;

        auto [s, c] = eve::sincos[o](iz);
        auto r = kyosu::exp[real_only][o.drop(raw)](rz);
        auto rr = Z(r * c, r * s);
        return rr;
      }
      else
      {
        auto negiz = eve::is_negative(imag(z));
        z = if_else(negiz, conj(z), z);
        auto [rz, iz] = z;
        auto r = kyosu::exp[real_only][o](rz);
        auto [s, c] = eve::sincos[o](iz);
        auto res = Z(r * c, r * s);
        imag(res) = if_else(negiz, -imag(res), imag(res));
        if (eve::none(eve::is_not_finite(z))) return res;
        else return corners(z, res);
      }
    }
    else
      return _::cayley_extend(kyosu::exp[o], z);
  }
}
