//==================================================================================================
/*
  KYOSU - Complex Without Complexes
  Copyright: KYOSU Project Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>

namespace kyosu
{
  template<typename Options>
  struct from_multipolar_t : eve::elementwise_callable<from_multipolar_t, Options>
  {
    template<concepts::real U ,concepts::real V,concepts::real W, concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()( V const & rho1
                                               , U const & theta1
                                               , W const & rho2
                                               , T const & theta2) const noexcept
    -> quaternion_t<eve::common_value_t<V, U, W, T>>
    {
      auto [a0, a1] = kyosu::from_polar(rho1, theta1);
      auto [a2, a3] = kyosu::from_polar(rho2, theta2);
      return kyosu::quaternion(a0, a1, a2, a3);
    }

    KYOSU_CALLABLE_OBJECT(from_multipolar_t, from_multipolar_);
  };
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
  //!     auto from_multipolar(auto rho1, auto theta1, auto rho2, auto theta2) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //! `rho1`, `rho2`:  the moduli
  //!
  //! `theta1`, `theta2`: the angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/from_multipolar.cpp}
  //======================================================================================================================
  inline constexpr auto from_multipolar = eve::functor<from_multipolar_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
