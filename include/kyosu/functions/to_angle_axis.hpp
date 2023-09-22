//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_to_angle_axis : eve::elementwise
  {
    using callable_tag_type = callable_to_angle_axis;

    KYOSU_DEFERS_CALLABLE(to_angle_axis_);

    template<eve::ordered_value V>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & v) noexcept
    {
      return kumi::tuple{V(0), std::array<V, 3>{V(1), V(0), V(0)}};
    }

    template<typename T0>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0))
    {
      return eve::tag_invoke(*this, target0);
    }

    template<typename... T>
    eve::unsupported_call<callable_to_angle_axis(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_angle_axis
  //!
  //! @brief Callable object computing the angle_axis coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of from_angle_axis
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
  //!     auto to_angle_axis( auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q` : quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple containing in this order `rho1`, 'theta1', `rho2` 'theta2':  the moduli
  //!  and  the angles in radian of the angle_axis \f$\mathbb{R}^4\f$ coordinates
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_angle_axis.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_to_angle_axis to_angle_axis = {};
}
