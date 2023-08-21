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
  struct callable_is_nez : eve::elementwise
  {
    using callable_tag_type = callable_is_nez;

    KYOSU_DEFERS_CALLABLE(is_nez_);

    template<eve::value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return v != T(0); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_is_nez(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_nez
//!   @brief test the parameter for non zero equality.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_nez(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr auto is_nez(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns the value of z != 0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_nez.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_is_nez is_nez = {};
}
