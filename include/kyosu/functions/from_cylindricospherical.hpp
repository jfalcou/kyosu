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
  struct from_cylindricospherical_t : eve::elementwise_callable<from_cylindricospherical_t, Options>
  {
    template<concepts::real U ,concepts::real V,concepts::real W, concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()(V const & t
                                               , U const & radius
                                               , W const & longitude
                                               , T const & latitude) const noexcept -> quaternion_t<eve::common_value_t<V, U, W, T>>
    {
      auto [slat, clat] = eve::sincos(latitude);
      auto [slon, clon] = eve::sincos(longitude);
      auto f = radius*clat;
      return kyosu::quaternion(t, f*clon, f*slon, radius*slat);
    }

    KYOSU_CALLABLE_OBJECT(from_cylindricospherical_t, from_cylindricospherical_);
  };

 //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_cylindrospherical
  //!
  //! @brief Callable object computing a quaternion from its cylindrospherical representation.
  //!
  //!  cylindrospherical is specific to quaternions. It is often interesting to consider
  //!  \f$\mathbb{H}\f$ as the cartesian product of \f$\mathbb{R}\f$ by \f$\mathbb{R}^3\f$
  //!  (the quaternionic multiplication has then a special form, as given here).
  //!  This function therefore builds a quaternion from this representation, with the \f$\mathbb{R}^3\f$ component given
  //!  in usual \f$\mathbb{R}^3\f$ spherical coordinates.
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
  //!     auto from_cylindrospherical(auto t, auto radius, auto longitude, auto latitude) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `t`, `radius`:  the moduli
  //!  * `longitude`, `latitude`: angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/from_cylindrospherical.cpp}
  //================================================================================================
  inline constexpr auto from_cylindricospherical = eve::functor<from_cylindricospherical_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
