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
  struct callable_from_cylindrical : eve::elementwise
  {
    using callable_tag_type = callable_from_cylindrical;

    KYOSU_DEFERS_CALLABLE(from_cylindrical_);

    template<eve::ordered_value V,  eve::ordered_value U,  eve::ordered_value W,  eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , V const & r
                                               , U const & angle
                                               , W const & h1
                                               , T const & h2) noexcept
    {
      using e_t = decltype(r+angle+h1+h2);
      auto [sa, ca] = eve::sincos(angle);
      return kyosu::quaternion(r*ca, r*sa, h1, h2);
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
    eve::unsupported_call<callable_from_cylindrical(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_cylindrical
  //!
  //! @brief Callable object computing a quaternion from its cylindrical representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a cylindrical representation of an \f$\mathbb{R}^2\f$ element.
  //!
  //! from_cylindrical first two inputs are the polar coordinates of the first \f$\mathbb{C}\f$
  //! component of the quaternion.
  //! The third and fourth inputs are placed into the third and fourth \f$\mathbb{R}\f$
  //! components of the quaternion, respectively.
  //!
  //! **Defined in header**
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
  //!     auto from_cylindrical(auto r, auto angle, auto h1, auto h2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `r`, angle`, `h1`, `h2`
  //!
  //! **Return value**
  //!
  //! the quaternion value.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_cylindrical.cpp}
  //!  @}
  //================================================================================================
  inline constexpr tags::callable_from_cylindrical from_cylindrical = {};
}
