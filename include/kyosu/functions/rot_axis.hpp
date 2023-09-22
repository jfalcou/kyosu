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
  struct callable_rot_axis : eve::elementwise
  {
    using callable_tag_type = callable_rot_axis;

    KYOSU_DEFERS_CALLABLE(rot_axis_);

    template<eve::ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & v) noexcept
    {
      return std::array<V, 3>{1, 0, 0};
    }

    template<typename T0>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0))
    {
      return eve::tag_invoke(*this, target0);
    }

    template<typename... T>
    eve::unsupported_call<callable_rot_axis(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rot_axis
  //!
  //! @brief Callable object computing the normalized axis of rotation defined by a quaternion.
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
  //!     auto rot_axis( auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q` : quaternion
  //!
  //! **Return value**
  //!
  //!  a span containing the three coordinates of the axis
  //!  if the quaternion is zero {1, 0, 0} is returned
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/regular/rot_axis.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_rot_axis rot_axis = {};
}
