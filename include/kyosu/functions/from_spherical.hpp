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
  struct from_spherical_t : eve::elementwise_callable<from_spherical_t, Options, rad_option, radpi_option>
  {
    template<concepts::real U, concepts::real V, concepts::real W, concepts::real T>
    KYOSU_FORCEINLINE constexpr quaternion_t<eve::common_value_t<V, U, W, T>> operator()(V const& rho,
                                                                                         U const& theta,
                                                                                         W const& phi1,
                                                                                         T const& phi2) const noexcept
    {
      auto o = this->options();
      auto [st, ct] = eve::sincos[o](theta);
      auto [sp1, cp1] = eve::sincos[o](phi1);
      auto [sp2, cp2] = eve::sincos[o](phi2);
      auto f = cp1 * cp2;
      return rho * quaternion(ct * f, st * f, sp1 * cp2, sp2);
    }

    KYOSU_CALLABLE_OBJECT(from_spherical_t, from_spherical_);
  };

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
  //!     auto from_spherical(auto rho, auto theta, auto phi1, auto phi2) const noexcept;
  //!     auto from_spherical[radpi](auto rho, auto theta, auto phi1, auto phi2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!   * `rho`:  the modulus
  //!   * `theta`, `phi1`, `phi2`: angles. If the `radpi`option  is used  the angles are returned in
  //!     `\f$\pi\f$ multiples else in radian.
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! #### Example
  //!
  //! @godbolt{doc/from_spherical.cpp}
  //======================================================================================================================
  inline constexpr auto from_spherical = eve::functor<from_spherical_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
