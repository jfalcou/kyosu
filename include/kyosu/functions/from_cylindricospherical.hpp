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
  struct callable_from_cylindrospherical : eve::elementwise
  {
    using callable_tag_type = callable_from_cylindrospherical;

    KYOSU_DEFERS_CALLABLE(from_cylindrospherical_);

    template<eve::ordered_value V,  eve::ordered_value U,  eve::ordered_value W,  eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & r
                                               , U const & angle
                                               , W const & h1
                                               , T const & h2) noexcept
    {
      auto [slat, clat] = eve::sincos(latitude);
      auto [slon, clon] = eve::sincos(longitude);
      auto f = r*clat;
      return kyosu::quaternion(t, f*clon, f*slon, r*slat);
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
    eve::unsupported_call<callable_from_cylindrospherical(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
 //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_cylindrospherical
  //!
  //! @brief Callable object computing a quaternion from its cylindrospherical representation.
  //!
  //!  cylindrospherical is specific to quaternions. It is often interesting to consider
  //!  \f$\mathbb{H}\f$ as the cartesian product of \f$\mathbb{R}\f$ by \f$\mathbb{R3}\f$
  //!  (the quaternionic multiplication has then a special form, as given here).
  //!  This function therefore builds a quaternion from this representation, with the \f$\mathbb{R3}\f$ component given
  //!  in usual \f$\mathbb{R3}\f$ spherical coordinates.
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
  //! @godbolt{doc/conversions.cpp}
  //!
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_cylindrospherical from_cylindrospherical = {};
}
