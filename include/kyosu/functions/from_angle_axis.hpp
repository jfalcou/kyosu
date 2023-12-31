//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/types/impl/quaternion/axis.hpp>
#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu::tags
{
  struct callable_from_angle_axis: eve::elementwise
  {
    using callable_tag_type = callable_from_angle_axis;

    KYOSU_DEFERS_CALLABLE(from_angle_axis_);

    template<eve::floating_ordered_value V,  typename  U>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V  angle
                                               , U  axis) noexcept
    {
      auto fn = callable_from_angle_axis{};
      return fn(angle, axis, normalize);
    }

    template<eve::floating_ordered_value V,  typename  U, bool n>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V  angle
                                               , U  axis
                                               , _::norming<n>) noexcept
    {
      using e_t = decltype(axis[0]+angle);
      auto q =  quaternion(e_t(0), e_t(axis[0]), e_t(axis[1]), e_t(axis[2]));
      if constexpr(n){
        q = if_else(is_eqz(q), quaternion(e_t(0), e_t(1)), sign(q));
      }
      auto [s, c] = eve::sincos(angle*eve::half(eve::as(angle)));
      return c+s*q;
    }

    template<typename T0, typename T1>
    KYOSU_FORCEINLINE auto operator()(T0 target0,
                                      T1 target1
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1))
    {
      return eve::tag_invoke(*this, target0,  target1);
    }

    template<typename T0, typename T1, bool n>
    KYOSU_FORCEINLINE auto operator()(T0 target0,
                                      T1 target1,
                                      _::norming<n> nr
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1, nr))
    {
      return eve::tag_invoke(*this, target0,  target1, nr);
    }

    template<typename... T>
    eve::unsupported_call<callable_from_angle_axis(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup functions
  //! @{
  //! @var from_angle_axis
  //!
  //! @brief Callable object computing an an unitary quaternion from an angle value
  //! and a 3 dimensionnal axis vector
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
  //!     auto from_angle_axis(auto angle,  auto axis, auto norming = normalize) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `angle`: rotation angle in radian
  //!  * `axis`: rotation axis given by an std::span of dimension 3.
  //!  * `normalize`: can be `assume_normalized` or `normalize`.
  //!      - In the second case the axis is normalized before use.
  //!      - if the axis is already normalized using `assume_normalized` is more efficient,
  //!        but the result is u.b. if it is not the case.
  //!      - if the axis is null the axis is normalized as (1, 0, 0).
  //!
  //! **Return value**
  //!
  //! the quaternion value representing the rotation.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_angle_axis.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_angle_axis from_angle_axis = {};
}
