//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_sqrt : eve::elementwise
  {
    using callable_tag_type = callable_sqrt;

    KYOSU_DEFERS_CALLABLE(sqrt_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto asq = eve::sqrt(eve::abs(v));
      return if_else(eve::is_gez(v), complex(asq, T(0)), complex(T(0), asq));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sqrt(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqrt
//!   @brief Computes a square root value.
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
//!      template<eve::floating_ordered_value T>     constexpr T sqrt(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T sqrt(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T sqrt(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to for which square root is computed.
//!
//!   **Return value**
//!
//!     1. a real typed input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!     2. Returns the elementwise the square root of z,
//!        in the range of the right half-plane, including the imaginary axis (\f$[0, +\infty]\f$
//!        along the real axis and \f$[-\infty, +\infty]\f$ along the imaginary axis.)
//!
//!        *  The function is continuous onto the branch cut taking into account
//!           the sign of imaginary part
//!        *  eve::sqrt(kyosu::conj(z)) == kyosu::conj(kyosu::sqrt(z))
//!        *  If z is \f$\pm0\f$, the result is \f$+0\f$
//!        *  If z is \f$x+i \infty\f$, the result is \f$\infty+i \infty\f$ even if x is \f$NaN\f$
//!        *  If z is \f$x,NaN\f$, the result is \f$NaN,NaN\f$ (unless x is \f$\pm\infty\f$)
//!        *  If z is \f$-\infty+i y\f$, the result is \f$+0+i \infty\f$ for finite positive y
//!        *  If z is \f$+\infty+i y\f$, the result is \f$+\infty+i 0\f$ for finite positive y
//!        *  If z is \f$-\infty+i NaN\f$, the result is \f$NaN \pm i \infty\f$ (sign of imaginary part unspecified)
//!        *  If z is \f$+\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!        *  If z is \f$NaN+i y\f$, the result is \f$NaN+i NaN\f$
//!        *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!     2. Returns a square root of z.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqrt.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sqrt sqrt = {};
}
