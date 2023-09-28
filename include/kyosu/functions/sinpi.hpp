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
  struct callable_sinpi : eve::elementwise
  {
    using callable_tag_type = callable_sinpi;

    KYOSU_DEFERS_CALLABLE(sinpi_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::sinpi(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sinpi(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinpi
//!   @brief Computes the sine of the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T sinpi(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T sinpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns the sine of the argument in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinpi.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sinpi sinpi = {};
}
