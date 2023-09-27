//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_nearest : eve::elementwise
  {
    using callable_tag_type = callable_nearest;

    KYOSU_DEFERS_CALLABLE(nearest_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::nearest(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_nearest(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var nearest
//!   @brief Computes the nearest value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T nearest(T z) noexcept;
//!      template<eve::floating_ordered_value T>              constexpr T nearest(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to for which nearest is computed.
//!
//!   **Return value**
//!
//!     Returns the nearest of its argument. i.e. the value with parts are the
//!     rounding to even of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/nearest.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_nearest nearest = {};
}
