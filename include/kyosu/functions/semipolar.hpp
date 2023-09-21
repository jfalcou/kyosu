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

namespace kyosu::tags
{
  struct callable_from_semipolar : eve::elementwise
  {
    using callable_tag_type = callable_from_semipolar;

    KYOSU_DEFERS_CALLABLE(from_semipolar_);

    template<eve::ordered_value V,  eve::ordered_value U,  eve::ordered_value W,  eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & rho
                                               , U const & alpha
                                               , W const & theta1
                                               , T const & theta2) noexcept
    {
      using z_t = eve::quaternion_t<U>;
      auto [st1, ct1] = eve::sincos(theta1);
      auto [st2, ct2] = eve::sincos(theta2);
      auto [sa, ca] = eve::sincos(alpha);
      return rho*quaternion(ca*ct1, ca*st1, sa*ct2, sa*st2);
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
    eve::unsupported_call<callable_from_semipolar(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_semipolar
  //!
  //! @brief Callable object computing a quaternion from its semipolar representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a semipolar representation of an \f$\mathbb{R}^4\f$ element.
  //!
  //!  from_semipolar takes as a first input the magnitude of the quaternion,
  //!  as a second input an angle in the range 0 to \f$\pi/2\f$ such that magnitudes of the first
  //!  two \f$\mathbb{C}\f$ components of the quaternion are the product of the first input and the sine and cosine
  //!  of this angle, respectively, and finally as third and fourth inputs angles in the range \f$-\pi/2\f$ to \f$+\pi/2\f$
  //!  which represent the arguments of the first and second \f$\mathbb{C}\f$ components of the quaternion, respectively.
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
  //!     auto from_semipolar(auto rho, auto alpha auto theta1, auto theta2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `rho`:  the modulus
  //!  * `alpha`, `theta1`, `theta2`: angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value representing the \f$\R^4\f$ element.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/conversions.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_semipolar from_semipolar = {};
}
