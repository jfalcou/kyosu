//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct exp_t : eve::elementwise_callable<exp_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::exp(v); }

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
//!      template<eve::floating_ordered_value T>     constexpr T exp(T z) noexcept; //1
//!      template<kyosu::concepts::ccomplex T>       constexpr T exp(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T exp(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns the exponential of the argument, calling `eve::exp`.
//!
//!     2. Returns the exponential of the complex input following IEEE standards:
//!
//!      * for every z: kyosu::exp(eve::conj(z)) == kyosu::conj(std::exp(z))
//!      * If z is \f$\pm0\f$, the result is \f$1\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$x+i NaN\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$+\infty+i 0\f$, the result is \f$+\infty\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite y), the result is \f$+0 \mathrm{cis}(y)\f$.
//!      * If z is \f$+\infty+i y\f$ (for any finite nonzero y), the result is \f$+\infty \mathrm{cis}(y)\f$.
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified)
//!      * If z is \f$+\infty+i \pm\infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$-\infty+i NaN\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified).
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$.
//!      * If z is \f$NaN+i y\f$ (for any nonzero y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$.
//!
//!     3.  Returns \f$e^{z_0}(\cos|\underline{z}|+\underline{z}\; \mathop{sinc}|\underline{z}|)\f$
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
    if constexpr(concepts::complex<Z> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto rho = eve::if_else(is_nan(rz), eve::allbits, eve::exp(rz));
      auto res = eve::if_else(is_real(z) || rz == eve::minf(eve::as(rz)),
                              complex(rho, eve::zero(eve::as(rho))),
                              complex(rho*c, rho*s));
      return if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), Z{rz, eve::nan(eve::as(iz))}, res);
    }
    else
    {
      return cayley_extend(exp, z);
    }
  }
}
