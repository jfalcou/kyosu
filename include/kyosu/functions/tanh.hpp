//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options> struct tanh_t : eve::elementwise_callable<tanh_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(tanh_t, tanh_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var tanh
  //!   @brief Computes the hyperbolic tangent of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T tanh(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     - returns eve::tanh(z).
  //!     - For complex input, returns elementwise the complex value  of the hyperbolic tangent of the input.
  //!
  //!       * for every z: `tanh(conj(z)) == conj(tanh(z))`
  //!       * for every z: `tanh(-z) == -tanh(z)`
  //!       * If z is \f$+0\f$, the result is \f$+0\f$
  //!       * If z is \f$x+i \infty\f$ (for any non zero finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
  //!       * If z is \f$i \infty\f$  the result is \f$i \textrm{NaN}\f$
  //!       * If z is \f$x,\textrm{NaN}\f$ (for any non zero finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
  //!       * If z is \f$i \textrm{NaN}\f$  the result is \f$i \textrm{NaN}\f$
  //!       * If z is \f$+\infty,y\f$ (for any finite positive y), the result is \f$1\f$
  //!       * If z is \f$+\infty+i \infty\f$, the result is \f$1,\pm 0\f$ (the sign of the imaginary part is unspecified)
  //!       * If z is \f$+\infty+i \textrm{NaN}\f$, the result is \f$1\f$ (the sign of the imaginary part is unspecified)
  //!       * If z is \f$\textrm{NaN}\f$, the result is \f$\textrm{NaN}\f$
  //!       * If z is \f$\textrm{NaN}+i y\f$ (for any non-zero y), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
  //!       * If z is \f$\textrm{NaN}+i \textrm{NaN}\f$, the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
  //!     - For general cayley_dickson input, the call is semantically equivalent to sinh(z)/cosh(z);
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/tanh.cpp}
  //======================================================================================================================
  inline constexpr auto tanh = eve::functor<tanh_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto tanh_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::tanh(z);
    else if constexpr (concepts::complex<Z>)
    {
      auto zz = z + z;
      auto [rz, iz] = zz;
      auto [s, c] = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto tmp = c + ch;
      auto rr = eve::if_else(eve::is_eqz(kyosu::real(z)), eve::zero, sh / tmp);
      auto ii = eve::if_else(kyosu::is_real(z), eve::zero, s / tmp);
      return kyosu::if_else(eve::is_infinite(rz), Z(eve::sign(rz)), Z(rr, ii));
    }
    else { return _::cayley_extend(kyosu::tanh, z); }
  }
}
