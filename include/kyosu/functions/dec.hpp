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
  struct callable_dec : eve::elementwise
  {
    using callable_tag_type = callable_dec;

    KYOSU_DEFERS_CALLABLE(dec_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::dec(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_dec(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dec
//!   @brief decrements the argument by 1.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #declude <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr T dec(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr T dec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to decrement.
//!
//!   **Return value**
//!
//!     Returns  its argument minus 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dec.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_dec dec = {};
}
