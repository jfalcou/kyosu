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
  struct callable_pure
  {
    using callable_tag_type = callable_pure;

    KYOSU_DEFERS_CALLABLE(pure_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::zero(eve::as(v)); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_pure(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pure
//!   @brief Extracts the imaginary part of a value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto& pure(T& z)        noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto  pure(T const& z)  noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T     pure(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Original value.
//!
//!   **Return value**
//!
//!     Returns the pure (olso called imaginary) part of its argument. For real inputs, the call returns 0. It is an alias of `imag`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/imag.cpp}
//======================================================================================================================
inline constexpr tags::callable_pure pure = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}
