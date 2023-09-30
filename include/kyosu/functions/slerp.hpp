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
  struct callable_slerp: eve::elementwise
  {
    using callable_tag_type = callable_slerp;

    KYOSU_DEFERS_CALLABLE(slerp_);

    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , eve::floating_ordered_value auto const& v0
                                               , eve::floating_ordered_value auto const& v1
                                              ,  eve::floating_ordered_value auto const& t) noexcept
    {
     EVE_ASSERT(eve::all(is_unitary(v0) && is_unitary(v1)), "quaternion parameters must be unitary");
     return v0;
    }

    KYOSU_FORCEINLINE auto operator()(auto const& target0, auto const& target1, auto const & target2) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1, target2))
    {
      return eve::tag_invoke(*this, target0, target1, target2);
    }

    template<typename... T>
    eve::unsupported_call<callable_slerp(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var slerp
//!   @brief  Computes the  spherical interpolation between unitary quaternions.
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
//!     constexpr auto lerp(auto z0, auto, z1, floating_ordered_value t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0, z1`: unitary quaternions to process.
//!     * `t`: floating value interpolation coefficient.
//!
//!   **Return value**
//!
//!    The value of the spherical interpolation (or extrapolation)  between `z0` and `z1` is returned.
//!    The functions asserts if the quaternions are not unitary.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/slerp.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_slerp slerp = {};
}
