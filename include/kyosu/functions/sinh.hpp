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
#include <kyosu/details/cayleyify.hpp>

namespace kyosu
{
  template<typename Options>
  struct sinh_t : eve::elementwise_callable<sinh_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sinh(v); }

    KYOSU_CALLABLE_OBJECT(sinh_t, sinh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinh
//!   @brief Computes the hyperbolic sine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto sinh(T z) noexcept; //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sinh(T z) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   1. Returns the hyperbolic sine of the argument.
//!
//!   2. Returns elementwise the complex value
//!      of the hyperbolic sine of the input.
//!
//!      * for every z: `eve::sinh(kyosu::conj(z)) == kyosu::conj(std::sinh(z))`
//!      * for every z: `kyosu::sinh(-z)           == -kyosu::sinh(z)`
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$i \infty\f$, the result is \f$i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$x+i NaN\f$ (for any positive finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$+\infty\f$, the result is \f$+\infty\f$
//!      * If z is \f$+\infty+i y\f$ (for any positive finite y), the result is \f$\infty\times e^{iy}\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$+\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$NaN+i y\f$ (for any finite nonzero y), the result is \f$NaN+i NaN\f$
//!
//!   3. Is semantically equivalent to (exp(z)-exp(-z))/2.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinh.cpp}
//======================================================================================================================
  inline constexpr auto sinh = eve::functor<sinh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sinh_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto r = c*sh;
      auto i = s*ch;
      if (eve::all(kyosu::is_finite(z))) return Z(r, i);
      auto infrz = kyosu::is_infinite(rz);
      auto nanrz = kyosu::is_nan(rz);
      if (eve::any(infrz || nanrz))
      {
        r = eve::if_else(infrz && eve::is_not_finite(iz), rz, r);
        i = eve::if_else(infrz && eve::is_nan(iz), eve::allbits, i);
        r = eve::if_else(nanrz, eve::allbits, r);
        i = eve::if_else(nanrz, eve::allbits, i);
      }
      i = eve::if_else(kyosu::is_real(z), eve::zero, i);
      r = eve::if_else(kyosu::is_eqz(kyosu::real(z)), eve::zero, r);
      return Z(r, i);
    }
    else
    {
      return cayley_extend(sinh, z);
    }
  }
}
