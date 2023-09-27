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
  struct callable_trunc : eve::elementwise
  {
    using callable_tag_type = callable_trunc;

    KYOSU_DEFERS_CALLABLE(trunc_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::trunc(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_trunc(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var trunc
//!   @brief Computes the trunc value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T trunc(T z) noexcept;
//!      template<eve::floating_ordered_value T>              constexpr T trunc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to for which trunc is computed.
//!
//!   **Return value**
//!
//!     Returns the truncation of its argument. i.e. the value with parts are the
//!     rounding toward zero of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/trunc.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_trunc trunc = {};
}
