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
#include <kyosu/functions/from_polar.hpp>

namespace kyosu::tags
{
  struct callable_from_multipolar : eve::elementwise
  {
    using callable_tag_type = callable_from_multipolar;

    KYOSU_DEFERS_CALLABLE(from_multipolar_);

    template<eve::ordered_value V,  eve::ordered_value U,  eve::ordered_value W,  eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & rho1
                                               , U const & theta1
                                               , W const & rho2
                                               , T const & theta2) noexcept
    {
      auto [a0, a1] = kyosu::from_polar(rho1, theta1);
      auto [a2, a3] = kyosu::from_polar(rho2, theta2);
      return kyosu::to_quaternion(a0, a1, a2, a3);
    }

    template<typename T0, typename T1, typename T2, typename T3>
    KYOSU_FORCEINLINE auto operator()(T0 const& target0,
                                      T1 const& target1,
                                      T2 const& target2,
                                      T3 const& target3
                                     ) const noexcept
    -> decltype(eve::tag_invoke(*this, target0,  target1,  target2,  target3))
    {
      return eve::tag_invoke(*this, target0,  target1,  target2,  target3);
    }

    template<typename... T>
    eve::unsupported_call<callable_from_multipolar(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_multipolar
  //!
  //! @brief Callable object computing a quaternion from its multipolar representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a multipolar representation of an \f$\mathbb{R}^4\f$ element.
  //!
  //!  from_multipolar  the two \f$\mathbb{C}\f$ components of the quaternion are given in polar coordinates
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
  //!     auto from_multipolar( auto rho1, auto theta1 auto rho2, auto theta2) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `rho1`, `rho2`:  the moduli
  //! 'theta1', 'theta2': the angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/conversions.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_multipolar from_multipolar = {};
}
