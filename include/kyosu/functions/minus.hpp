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
  struct callable_minus : eve::elementwise
  {
    using callable_tag_type = callable_minus;

    KYOSU_DEFERS_CALLABLE(minus_);

    template<eve::value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return -v; }
    // there is no other implementation

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_minus(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var minus
//!   @brief Computes the opposite value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T minus(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr T minus(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to minusugate.
//!
//!   **Return value**
//!
//!     Returns the opposite of its argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/minus.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_minus minus = {};
}
