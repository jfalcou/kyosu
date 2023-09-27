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
  struct callable_manhattan : eve::elementwise
  {
    using callable_tag_type = callable_manhattan;

    KYOSU_DEFERS_CALLABLE(manhattan_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const&... vs) noexcept
    {
      return eve::manhattan(vs...);
    }

    KYOSU_FORCEINLINE auto operator()(auto const&... targets ) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

//     template<typename... T>
//     eve::unsupported_call<callable_manhattan(T&&...)> operator()(T&&... x) const
//     requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var manhattan
//!   @brief Callable object computing the manhattan operation.
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
//!      template< floating_value P, typename ... Ts>
//!      auto operator()(Ts ... zi ) const noexcept
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * ` zi...` : Values to process.
//!
//!   **Return value**
//!
//!     Returns the sum of the absolute values of all elements of all zi.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/manhattan.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_manhattan manhattan = {};
}
