//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/arg.hpp>
#include <kyosu/details/axis.hpp>

namespace kyosu
{
  template<typename Options> struct to_angle_axis_t : eve::elementwise_callable<to_angle_axis_t, Options>
  {
    template<typename Q>
    requires((concepts::cayley_dickson<Q> && dimension_v<Q> <= 4) || concepts::real<Q>)
    KYOSU_FORCEINLINE constexpr auto operator()(Q q0) const noexcept
    {
      auto q = quaternion(sign(q0));
      using e_t = std::decay_t<decltype(real(q))>;
      auto ap = kyosu::abs(pure(q));
      auto invn = eve::rec(ap);
      invn = eve::if_else(eve::is_infinite(invn), eve::zero, invn);
      std::array<e_t, 3> v{kyosu::ipart(q) * invn, kyosu::jpart(q) * invn, kyosu::kpart(q) * invn};
      auto a = 2 * eve::atan2[eve::pedantic](ap, kyosu::real(q));
      return kumi::tuple{a, v};
    }

    KYOSU_CALLABLE_OBJECT(to_angle_axis_t, to_angle_axis_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_angle_axis
  //!
  //! @brief Callable object computing the angle and axis coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of `from_angle_axis`
  //!
  //! @groupheader{Header file}
  //!
  //!   @code
  //!   #include kyosu/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     auto to_angle_axis(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple an angle of rotation and a vector of \f$\mathbb{R}^3\f$
  //!  representing the direction of the rotation axis.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_angle_axis.cpp}
  //================================================================================================
  inline constexpr auto to_angle_axis = eve::functor<to_angle_axis_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
