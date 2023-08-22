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
  struct callable_lerp : eve::elementwise
  {
    using callable_tag_type = callable_lerp;

    KYOSU_DEFERS_CALLABLE(lerp_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::ordered_value auto const& v0
                                               , eve::ordered_value auto const& v1
                                              ,  eve::ordered_value auto const& t) noexcept
    {
      return eve::lerp(v0, v1, t);
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1, auto const & target2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, target2))
    {
      return eve::tag_invoke(*this, target0, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_lerp(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lerp
//!   @brief  Computes the  linear interpolation.
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
//!      template<kyosu::concepts::cayley_dickson T0, kyosu::concepts::cayley_dickson T1 > constexpr auto lerp(T0 z0, T1, z1, auto eve::ordered_value t) noexcept;
//!      template<eve::ordered_value T0, kyosu::concepts::cayley_dickson T1>             > constexpr auto lerp(T0 z0, T1, z1, auto eve::ordered_value t) noexcept;
//!      template<kyosu::concepts::cayley_dickson T0,  eve::ordered_value T1             > constexpr auto lerp(T0 z0, T1, z1, auto eve::ordered_value t) noexcept;
//!      template<eve::ordered_value T0, ordered_value T1>                               > constexpr auto lerp(T0 z0, T1, z1, auto eve::ordered_value t) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1` : Value to process.
//!     * `t` : interpolation coefficient
//!
//!   **Return value**
//!
//!    The value of the interpolation (or extrapolation)  between `z0` and `z1` is returned.
//!    The call is semantically equivalent to `z0+t*(z1-z0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lerp.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_lerp lerp = {};
}
