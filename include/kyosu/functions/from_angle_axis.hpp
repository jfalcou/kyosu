//==================================================================================================
/*
  KYOSU - Complex Without Complexes
  Copyright: KYOSU Project Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/details/axis.hpp>
#include <kyosu/functions/sign.hpp>

namespace kyosu
{
  template<typename Options>
  struct from_angle_axis_t : eve::strict_elementwise_callable<from_angle_axis_t, Options, assume_unitary_option>
  {

    template< concepts::real V, concepts::real T, std::size_t S>
    KYOSU_FORCEINLINE constexpr auto operator()( V  angle
                                               , std::span<T, S> axis) const noexcept
    -> quaternion_t<eve::common_value_t<V, T>>
    {
      using e_t = eve::common_value_t<T, V>;
      auto q =  quaternion(e_t(0), e_t(axis[0]), e_t(axis[1]), e_t(axis[2]));
      if constexpr(!Options::contains(assume_unitary)){
        q = if_else(is_eqz(q), quaternion(e_t(0), e_t(1)), sign(q));
      }
      auto [s, c] = eve::sincos(angle*eve::half(eve::as(angle)));
      return c+s*q;
    }

    KYOSU_CALLABLE_OBJECT(from_angle_axis_t, from_angle_axis_);
  };

 //================================================================================================
  //! @addtogroup functions
  //! @{
  //! @var from_angle_axis
  //!
  //! @brief Callable object computing an an unitary quaternion from an angle value
  //! and a 3 dimensional axis vector
  //!
  //! @groupheader{Header file}
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
  //!     auto from_angle_axis(auto angle, auto axis) const noexcept;
  //!     auto from_angle_axis[assume_unitary](auto angle, auto axis) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `angle`: rotation angle in radian
  //!  * `axis`: rotation axis given by an std::span of dimension 3.
  //!
  //! **Return value**
  //!
  //!   1. the quaternion value representing the rotation.
  //!      (if the axis is null the axis is normalized as (1, 0, 0)).
  //!   2. with `assume_unitary` the axis is NOT normalized before use,
  //!        but the result is undefined if it is not the case.
  //!
  //! @groupheader{Example}
  //! @godbolt{doc/from_angle_axis.cpp}
  //======================================================================================================================
  inline constexpr auto from_angle_axis = eve::functor<from_angle_axis_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
