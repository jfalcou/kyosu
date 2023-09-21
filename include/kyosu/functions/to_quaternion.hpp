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
  struct callable_quaternion
  {
    using callable_tag_type = callable_quaternion;

    KYOSU_DEFERS_CALLABLE(quaternion_);

    template<typename... T>
    KYOSU_FORCEINLINE auto operator()(T... target) const noexcept -> decltype(eve::tag_invoke(*this, target...))
    {
      return eve::tag_invoke(*this, target...);
    }

    template<typename... T>
    eve::unsupported_call<callable_quaternion(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var quaternion
//!   @brief Constructs a kyosu::quaternion
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
//!      template<eve::ordered_value T> constexpr auto quaternion(T r)                      noexcept;
//!      template<eve::ordered_value T> constexpr auto quaternion(T r, T i, T j, T k)       noexcept;

//!      template<kyosu::concepts::cayley_dickson T> constexpr T quaternion(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`                 : Quaternion value.
//!     * `r`, `i`, `j`, `k`  : Real and unreal parts sued to construct a @ref kyosu::quaternion..
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::quaternion constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/quaternion.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_quaternion quaternion = {};
}
