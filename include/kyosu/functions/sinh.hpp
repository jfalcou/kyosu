//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_sinh : eve::elementwise
  {
    using callable_tag_type = callable_sinh;

    KYOSU_DEFERS_CALLABLE(sinh_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::sinh(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sinh(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinh
//!   @brief Computes the hyperbolic sine of the argument.
//!
//!   **Defined in Header**
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
//!     * `z` : Value to process.
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
//! @}
//======================================================================================================================
inline constexpr tags::callable_sinh sinh = {};
}
