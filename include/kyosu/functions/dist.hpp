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
  struct callable_dist: eve::elementwise
  {
    using callable_tag_type = callable_dist;

    KYOSU_DEFERS_CALLABLE(dist_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1) noexcept
    {
      return eve::dist(v0, v1);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1 ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_dist(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dist
//!   @brief Computes the distance between the two parameters.
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
//!     constexpr auto dist(auto z0,  auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the distance between the two arguments computed as the absolute value of the arguments difference.
//!     Arguments can be a mix of floting or Cayley-Dicson values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dist.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_dist dist = {};
}
