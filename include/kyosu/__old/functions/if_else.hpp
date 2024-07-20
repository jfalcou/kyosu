//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_if_else: eve::elementwise
  {
    using callable_tag_type = callable_if_else;

    KYOSU_DEFERS_CALLABLE(if_else_);

    template<eve::floating_ordered_value T, eve::floating_ordered_value U>
    static KYOSU_FORCEINLINE auto deferred_call(auto, auto c, T const& t, U u) noexcept { return eve::if_else(c, t, u); }

    KYOSU_FORCEINLINE
    auto operator()(auto const& m, auto const& t, auto const& f) const noexcept -> decltype(eve::tag_invoke(*this,m,t,f))
    {
      return eve::tag_invoke(*this, m, t, f);
    }

    template<typename... T>
    eve::unsupported_call<callable_if_else(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var if_else
//!   @brief Select a value between two arguments based on a logical mask
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
//!     constexpr auto if_else(auto x, auto y, auto z ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: logical mask.
//!     * `y`, `z`: values to be selected.
//!
//!   **Return value**
//!
//!        elementwise `y` or `z` according the truth value of `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/if_else.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_if_else if_else = {};
}
