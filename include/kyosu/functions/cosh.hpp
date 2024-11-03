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
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/details/cayleyify.hpp>

namespace kyosu
{
  template<typename Options>
  struct cosh_t : eve::elementwise_callable<cosh_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cosh(v); }

    KYOSU_CALLABLE_OBJECT(cosh_t, cosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cosh
//!   @brief Computes the hyperbolic cosine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr T cosh(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T cosh(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T cosh(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   2. Returns elementwise the complex value
//!      of the hyperbolic cosine of the input.
//!
//!      * for every z: `kyosu::cosh(kyosu::conj(z)) == kyosu::conj(std::cosh(z))`
//!      * for every z: `kyosu::cosh(-z)           == kyosu::cosh(z)`
//!      *  If z is \f$0\f$, the result is \f$1\f$
//!      *  If z is \f$i \infty\f$, the result is \f$NaN\f$
//!      *  If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$x+i \infty\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$x+i NaN\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$\infty+i 0\f$, the result is \f$\infty+i 0\f$
//!      *  If z is \f$\infty,y\f$ (for any finite non-zero y), the result is \f$\infty e^{iy}\f$
//!      *  If z is \f$\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$  (the sign of the real part is unspecified)
//!      *  If z is \f$\infty+i NaN\f$, the result is \f$\infty+i NaN\f$
//!      *  If z is \f$NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$NaN+i y\f$ (for any finite non-zero y), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!   3. Is semantically equivalent to (exp(z)+exp(-z))/2.

//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cosh.cpp}
//======================================================================================================================
  inline constexpr auto cosh = eve::functor<cosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cosh_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto r = c*ch;
      auto i = s*sh;
      i = eve::if_else(kyosu::is_eqz(kyosu::ipart(z)) || kyosu::is_real(z), eve::zero, i);
      auto res = Z(r, i);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        res = eve::if_else(eve::is_infinite(rz) && eve::is_not_finite(iz), Z(eve::inf(eve::as(rz)), eve::nan(eve::as(rz))), res);
        res = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz),        Z(eve::nan(eve::as(rz)), eve::nan(eve::as(rz))), res);
      }
      return res;
    }
    else
    {
      return cayley_extend(cosh, z);
    }
  }
}
