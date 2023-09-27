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
  struct callable_is_unitary : eve::elementwise
  {
    using callable_tag_type = callable_is_unitary;

    KYOSU_DEFERS_CALLABLE(is_unitary_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::abs(v) == eve::one(eve::as(v)); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_is_unitary(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_unitary
//!   @brief test if the parameter is unitary (absolute value one).
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_unitary(T z) noexcept;
//!      template<eve::floating_ordered_value T>              constexpr auto is_unitary(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if an element is of absolute value one.
//!
//!   @note As for now is_unitary accepts almost equality (will change when decorators will be at hand in kyosu)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_unitary.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_is_unitary is_unitary = {};
}
