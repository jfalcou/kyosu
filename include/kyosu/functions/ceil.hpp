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
  struct callable_ceil : eve::elementwise
  {
    using callable_tag_type = callable_ceil;

    KYOSU_DEFERS_CALLABLE(ceil_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::ceil(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_ceil(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var ceil
//!   @brief Computes the ceil value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T ceil(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T ceil(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value for which ceil is computed.
//!
//!   **Return value**
//!
//!     Returns the ceil of its argument. i.e. the value with parts are the ceil of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/ceil.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_ceil ceil = {};
}
