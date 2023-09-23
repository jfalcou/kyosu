//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_rot_angle : eve::elementwise
  {
    using callable_tag_type = callable_rot_angle;

    KYOSU_DEFERS_CALLABLE(rot_angle_);

    template<eve::ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & v) noexcept
    {
      return eve::zero(as(v));
    }

    template<typename T0>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0))
    {
      return eve::tag_invoke(*this, target0);
    }

    template<typename... T>
    eve::unsupported_call<callable_rot_angle(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rot_angle
  //!
  //! @brief Callable object computing the normalized angle of rotation defined by a quaternion.
  //!
  //!  This function is the reciprocal of from_polar
  //!
  //! **Defined in header**
  //!
  //!   @code
  //!   #include eve/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     auto rot_angle( auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q` : quaternion
  //!
  //! **Return value**
  //!
  //!  the rotation angle in radian
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/rot_angle.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_rot_angle rot_angle = {};
}
