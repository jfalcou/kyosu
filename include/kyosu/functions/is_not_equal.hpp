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
  struct callable_is_not_equal: eve::elementwise
  {
    using callable_tag_type = callable_is_not_equal;

    KYOSU_DEFERS_CALLABLE(is_not_equal_);


    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::value auto const& v0
                                               , eve::value auto const& v1) noexcept
    {
      return v0 != v1;
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1 ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_is_not_equal(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_not_equal
//!   @brief return true if and only if the two parameters are not equal.
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
//!      constexpr auto is_equal(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elemtwise true or false according the inequality of the parameters
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_not_equal.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_is_not_equal is_not_equal = {};
}
