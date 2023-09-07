//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright : KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/impl/quaternion/axes.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_from_angle_axis : eve::elementwise
  {
    using callable_tag_type = callable_from_angle_axis;

    KYOSU_DEFERS_CALLABLE(from_angle_axis_);

    template<eve::ordered_value V,  eve::ordered_value U, bool normalize>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & angle
                                               , std::span<U, 3>  axis
                                              , nor<normalize>) noexcept
    {
      if constexpr (!normalize)
      {
        auto q =  to_quaternion(U(0), axis[0], axis[1], axis[2]);
        EVE_ASSERT(eve::all(is_unitary(q)), "some axies are not unitary");
        auto [c, s] = eve::sincos(angle*eve::half(as(angle)));
        return c+ s*q;
      }
      else
      {
        auto n = eve::rec(eve::pedantic(eve::hypot)(axis[0], axis[1], axis[2]));
        axis[0]*= n;
        axis[1]*= n;
        axis[2]*= n;
        return to_angle_axis(angle, axis, Assume_normalized);
      }
    }

    template<eve::ordered_value V,  eve::ordered_value U>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & angle
                                               , std::span<U, 3>const & axis) noexcept
    {
       return to_angle_axis(angle, axis, Normalize);
    }

    template<eve::ordered_value T0,  eve::ordered_value T1, bool normalize>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0,
                                      T1 const& target1,
                                      nor<normalize> const & target2
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1, target2))
    {
      return eve::tag_invoke(*this, target0,  target1, target2);
    }

    template<typename T0, typename T1>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0,
                                      T1 const& target1
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1))
    {
      return eve::tag_invoke(*this, target0,  target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_from_angle_axis(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_angle_axis
  //!
  //! @brief Callable object computing a quaternion from its angle_axis representation.
  //!
  //!  This function build an unitary quaternion from an angle value and a 3 dimensionnal axis vector
  //!
  //! **Defined in header**
  //!
  //!   @code
  //!   #include kyosu/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace kyosu
  //!   {
  //!     auto from_angle_axis(auto angle,  auto axis, auto normalize = Normalize) const noexcept;

  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `angle` : rotation angle in radian
  //!  * `axis`` : rotation axis given by an std::span of dimension 3.
  //!  * normalize : can be Assume_normalized or Normalize in the second case axis is normalized.
  //!                if axis is already normalized use Assume_normalized.
  //!
  //! **Return value**
  //!
  //! the quaternion value representing the rotation.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/conversions.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_angle_axis from_angle_axis = {};
}
