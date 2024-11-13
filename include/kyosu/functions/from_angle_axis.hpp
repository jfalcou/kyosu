//==================================================================================================
/*
  KYOSU - Complex Without Complexes
  Copyright: KYOSU Project Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/types/impl/quaternion/axis.hpp>
#include <kyosu/functions/sign.hpp>

namespace kyosu
{
  template<typename Options>
  struct from_angle_axis_t : eve::strict_elementwise_callable<from_angle_axis_t, Options>
  {

    template< concepts::real V, concepts::real T, std::size_t S, bool n>
    KYOSU_FORCEINLINE constexpr auto operator()( V  angle
                                               , std::span<T, S> axis
                                               , _::norming<n>) const noexcept
    -> quaternion_t<eve::common_value_t<V, T>>
    {
      using e_t = eve::common_value_t<T, V>;
      auto q =  quaternion(e_t(0), e_t(axis[0]), e_t(axis[1]), e_t(axis[2]));
      if constexpr(n){
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
  //!     auto from_angle_axis(auto angle, auto axis, auto norming) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `angle`: rotation angle in radian
  //!  * `axis`: rotation axis given by an std::span of dimension 3.
  //!  * `norming`: can be `assume_normalized` or `normalize`.
  //!      - In the second case the axis is normalized before use.
  //!      - if the axis is already normalized using `assume_normalized` is more efficient,
  //!        but the result is undefined behavior if it is not the case.
  //!      - if the axis is null the axis is normalized as (1, 0, 0).
  //!
  //! **Return value**
  //!
  //! the quaternion value representing the rotation.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_angle_axis.cpp}
  //======================================================================================================================
  inline constexpr auto from_angle_axis = eve::functor<from_angle_axis_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
