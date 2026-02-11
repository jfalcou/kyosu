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

namespace kyosu
{
  template<typename Options> struct rot_angle_t : eve::elementwise_callable<rot_angle_t, Options>
  {

    template<concepts::cayley_dickson Z>
    requires(dimension_v<Z> <= 4)
    KYOSU_FORCEINLINE constexpr auto operator()(Z const& q) const noexcept
    {
      return 2 * eve::atan2[eve::pedantic](kyosu::abs(kyosu::pure(q)), kyosu::real(q));
    }

    KYOSU_CALLABLE_OBJECT(rot_angle_t, rot_angle_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rot_angle
  //!
  //! @brief Callable object computing the normalized angle of rotation defined by a quaternion.
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
  //!     auto rot_angle(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion, complex or floating
  //!
  //! **Return value**
  //!
  //!  the rotation angle in radian. This is two times the arg of the quaternion.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/rot_angle.cpp}
  //================================================================================================
  inline constexpr auto rot_angle = eve::functor<rot_angle_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
