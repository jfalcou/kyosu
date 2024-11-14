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
  template<typename Options>
  struct rot_axis_t : eve::elementwise_callable<rot_axis_t, Options>
  {

    template<concepts::cayley_dickson Z>
    requires(dimension_v<Z> <= 4)
      KYOSU_FORCEINLINE constexpr auto operator()(Z const& q) const noexcept
    {
    using e_t = as_real_type_t<Z>;
    auto invn = eve::rec(kyosu::abs(kyosu::pure(q)));
    invn = eve::if_else(eve::is_nan(invn), eve::zero, invn);
    std::array<e_t, 3> v{kyosu::ipart(q)*invn, kyosu::jpart(q)*invn, kyosu::kpart(q)*invn};
    return v;

    }

    KYOSU_CALLABLE_OBJECT(rot_axis_t, rot_axis_);
  };

 //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rot_axis
  //!
  //! @brief Callable object computing the normalized axis of rotation defined by a quaternion.
  //!
  //! @groupheader{Header file}
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
  //!     auto rot_axis(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion, complex or floating.
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
  //! @godbolt{doc/rot_axis.cpp}
  //================================================================================================
  inline constexpr auto rot_axis = eve::functor<rot_axis_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
