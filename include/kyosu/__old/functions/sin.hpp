//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_sin: eve::elementwise
  {
    using callable_tag_type = callable_sin;

    KYOSU_DEFERS_CALLABLE(sin_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::sin(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sin(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sin
//!   @brief Computes the sine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto sin(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr auto sin(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sin(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns the sine of the argument.
//!
//!     2. The behavior of this function is equivalent to \f$-i*\sinh(i*z)\f$.
//!
//!     3.  Returns \f$-I_z\cosh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\sin(z_0)\f$,
//!       where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!        \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sin.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sin sin = {};
}
