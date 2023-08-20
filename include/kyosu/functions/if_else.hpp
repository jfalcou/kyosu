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
  struct callable_if_else : eve::elementwise
  {
    using callable_tag_type = callable_if_else;

    KYOSU_FORCEINLINE
    auto operator()(auto const& m, auto const& t, auto const& f) const noexcept -> decltype(eve::tag_invoke(*this,m,t,f))
    {
      return eve::tag_invoke(*this, m, t, f);
    }

    // template<typename... T>
    // eve::unsupported_call<callable_if_else(T&&...)> operator()(T&&... x) const
    // requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
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
//!      template<eve::value T, eve::value U, eve::value V>
//!      constexpr auto if_else(T x, U, y, V z ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/if_else.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_if_else if_else = {};
}
