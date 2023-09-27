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
  struct callable_dot : eve::elementwise
  {
    using callable_tag_type = callable_dot;

    KYOSU_DEFERS_CALLABLE(dot_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1) noexcept
    {
      return eve::dot(v0, v1);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1 ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_dot(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dot
//!   @brief Computes elementwise the dot product of the coordinates of the corresponding element.
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
//!      template<kyosu::concepts::cayley_dickson T0, kyosu::concepts::cayley_dickson T1 > constexpr auto dot(T0 z0, T1, z1) noexcept;
//!      template<eve::floating_ordered_value T0, kyosu::concepts::cayley_dickson T1>             > constexpr auto dot(T0 z0, T1, z1) noexcept;
//!      template<kyosu::concepts::cayley_dickson T0,  eve::floating_ordered_value T1             > constexpr auto dot(T0 z0, T1, z1) noexcept;
//!      template<eve::floating_ordered_value T0, floating_ordered_value T1>                               > constexpr auto dot(T0 z0, T1, z1) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1` : Value to process.
//!
//!   **Return value**
//!
//!     Returns the dot product of z0 and z1. If z0 and z1 are floating point this is equivalent to z0*z1.
//!
//!     `dot(z0, z0)` is always semantically equivalent to `sqr_abs(z0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dot.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_dot dot = {};
}
