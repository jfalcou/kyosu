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

namespace kyosu
{
  template<typename Options>
  struct exp_t : eve::elementwise_callable<exp_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T exp(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!      - Returns the exponential of the argument, calling `eve::exp`.
//!
//!      - For complex inpus, returns the exponential of the complex input following IEEE standards:
//!
//!       * for every z: `exp(conj(z)) == conj(exp(z))`
//!       * If z is \f$\pm0\f$, the result is \f$1\f$
//!       * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
//!       * If z is \f$x+i \textrm{NaN}\f$ (for any finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
//!       * If z is \f$+\infty+i 0\f$, the result is \f$+\infty\f$
//!       * If z is \f$-\infty+i y\f$ (for any finite y), the result is \f$+0 e^{iy}\f$.
//!       * If z is \f$+\infty+i y\f$ (for any finite nonzero y), the result is \f$+\infty e^{iy}\f$.
//!       * If z is \f$-\infty+i \infty\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified)
//!       * If z is \f$+\infty+i \pm\infty\f$, the result is \f$\pm \infty+i \textrm{NaN}\f$ (the sign of the real part is unspecified).
//!       * If z is \f$-\infty+i \textrm{NaN}\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified).
//!       * If z is \f$\pm\infty+i \textrm{NaN}\f$, the result is \f$\pm \infty+i \textrm{NaN}\f$ (the sign of the real part is unspecified).
//!       * If z is \f$\textrm{NaN}\f$, the result is \f$\textrm{NaN}\f$.
//!       * If z is \f$\textrm{NaN}+i y\f$ (for any nonzero y), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
//!       * If z is \f$\textrm{NaN}+i \textrm{NaN}\f$, the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
//!
//!     - For generate cayley-dickson inputs, returns \f$e^{z_0}(\cos|\underline{z}|+\underline{z}\; \mathop{sinc}|\underline{z}|)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp.cpp}
//======================================================================================================================
  inline constexpr auto exp = eve::functor<exp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto exp_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z> )
      return eve::exp(z);
    else if constexpr(concepts::complex<Z> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto rho = eve::if_else(is_nan(rz), eve::allbits, eve::exp(rz));
      auto res = eve::if_else(is_real(z) || rz == eve::minf(eve::as(rz)),
                              Z(rho, eve::zero(eve::as(rho))),
                              Z(rho*c, rho*s));
      return if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), Z{rz, eve::nan(eve::as(iz))}, res);
    }
    else
    {
      return _::cayley_extend(kyosu::exp, z);
    }
  }
}
