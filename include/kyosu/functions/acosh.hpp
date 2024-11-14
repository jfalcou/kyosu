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
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/acos.hpp>


namespace kyosu
{
  template<typename Options>
  struct acosh_t : eve::elementwise_callable<acosh_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(acosh_t, acosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acosh
//!   @brief Computes the inverse hyperbolic cosine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acosh(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto acosh(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acosh(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if `complex(z)` was entered.
//!
//!   2. Returns the complex inverse hyperbolic cosine of z, in the range of a
//!      strip unbounded along the imaginary axis and
//!      in the interval \f$[0,\pi]\f$ along the real axis.
//!
//!      * for every z: acosh(conj(z)) ==conj(acosh(z))
//!      * If z is \f$\pm0\f$, the result is \f$+0+i\pi/2\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\infty+i\pi/2\f$
//!      * If z is \f$x+i NaN\f$ (for any finite non zero x), the result is \f$NaN+iNaN\f$.
//!      * If z is \f$i NaN\f$  the result is \f$NaN+i\pi/2\f$.
//!      * If z is \f$-\infty,y\f$ (for any positive finite y), the result is \f$+\infty,\pi\f$
//!      * If z is \f$+\infty,y\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$+\infty,3\pi/4\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN,y\f$ (for any finite y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i \infty\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!   3. Returns \f$\log(z+\sqrt{z+1}\sqrt{z-1})\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acosh.cpp}
//======================================================================================================================
  inline constexpr auto acosh = eve::functor<acosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acosh_(KYOSU_DELAY(), O const&, Z a0) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // acosh(a0) = +/-i acos(a0)
      // Choosing the sign of multiplier to give real(acosh(a0)) >= 0
      // we have compatibility with C99.
      auto [r, i] = kyosu::acos(a0);
      auto lez = eve::is_negative(i);;
      auto res = complex(-i, r);
      res = eve::if_else(lez, res, -res);
      auto nani = eve::is_nan(i);
      if (eve::any(nani))
        return eve::if_else(nani && eve::is_finite(r)
                           , complex(eve::nan(eve::as(r)), eve::nan(eve::as(r)))
                           , res);
      else
        return res;
    }
    else
    {
      return cayley_extend(acosh, a0);
    }
  }
}
