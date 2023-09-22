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
  struct callable_from_spherical : eve::elementwise
  {
    using callable_tag_type = callable_from_spherical;

    KYOSU_DEFERS_CALLABLE(from_spherical_);

    template<eve::ordered_value V,  eve::ordered_value U,  eve::ordered_value W,  eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & rho
                                               , U const & theta
                                               , W const & phi1
                                               , T const & phi2) noexcept
    {
      auto [st, ct] = eve::sincos(theta);
      auto [sp1, cp1] = eve::sincos(phi1);
      auto [sp2, cp2] = eve::sincos(phi2);
      auto f = cp1*cp2;
      return rho*quaternion(ct*f, st*f, sp1*cp2, sp2);
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
    eve::unsupported_call<callable_from_spherical(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_spherical
  //!
  //! @brief Callable object computing a quaternion from its spherical representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a spherical representation of an \f$\mathbb{R}^4\f$ element.
  //!
  //!  from_spherical takes as inputs a (positive) magnitude and a point on the hypersphere, given by three angles.
  //!  The first of these, theta has a natural range of \f$-\pi\f$ to \f$+\pi\f$, and the other two have natural
  //!  ranges of \f$-\pi/2\f$ to \f$+\pi/2\f$ (as is the case with the usual spherical coordinates in \f$\mathbb{R}^3\f$).
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
  //!     auto from_spherical(auto rho, auto theta, auto phi1, auto phi2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!   * `rho`:  the modulus
  //!   * `theta`, 'phi1`, 'phi2`: angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/conversions.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_spherical from_spherical = {};
}
