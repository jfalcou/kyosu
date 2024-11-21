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
  struct from_semipolar_t : eve::elementwise_callable<from_semipolar_t, Options>
  {
    template<concepts::real U ,concepts::real V,concepts::real W, concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()( V const & rho
                                               , U const & alpha
                                               , W const & theta1
                                               , T const & theta2) const noexcept
    -> quaternion_t<eve::common_value_t<V, U, W, T>>
    {
      auto [st1, ct1] = eve::sincos(theta1);
      auto [st2, ct2] = eve::sincos(theta2);
      auto [sa, ca]   = eve::sincos(alpha);
      return rho*kyosu::quaternion(ca*ct1, ca*st1, sa*ct2, sa*st2);
    }

    KYOSU_CALLABLE_OBJECT(from_semipolar_t, from_semipolar_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_semipolar
  //!
  //! @brief Callable object computing a quaternion from its semipolar representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a polar representation of an \f$\mathbb{R}^2\f$ element.
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
  //!     auto from_semipolar(auto rho, auto alpha, auto theta1, auto theta2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `r`, `alpha`, `theta1`, `theta2`
  //!
  //! **Return value**
  //!
  //! the quaternion value.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_semipolar.cpp}
  //======================================================================================================================
  inline constexpr auto from_semipolar = eve::functor<from_semipolar_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
