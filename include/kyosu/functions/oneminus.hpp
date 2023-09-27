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
  struct callable_oneminus : eve::elementwise
  {
    using callable_tag_type = callable_oneminus;

    KYOSU_DEFERS_CALLABLE(oneminus_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::oneminus(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_oneminus(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var oneminus
//!   @brief Computes the value 1 minus the argument.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #oneminuslude <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr T oneminus(T z) noexcept;
//!      template<eve::floating_ordered_value T>              constexpr T oneminus(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : argument.
//!
//!   **Return value**
//!
//!     Returns 1 minus the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/oneminus.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_oneminus oneminus = {};
}
