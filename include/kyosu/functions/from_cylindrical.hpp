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
  struct from_cylindrical_t : eve::elementwise_callable<from_cylindrical_t, Options>
  {
    template<concepts::real U ,concepts::real V,concepts::real W, concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()( V const& r
                                               , U const & angle
                                               , W const & h1
                                               , T const & h2) const noexcept
    -> quaternion_t<eve::common_value_t<V, U, W, T>>
    {
      auto [sa, ca] = eve::sincos(angle);
      return kyosu::quaternion(r*ca, r*sa, h1, h2);
    }

    KYOSU_CALLABLE_OBJECT(from_cylindrical_t, from_cylindrical_);
  };

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
  //! `from_cylindrical` first two inputs are the polar coordinates of the first \f$\mathbb{C}\f$
  //! component of the quaternion.
  //! The third and fourth inputs are placed into the third and fourth \f$\mathbb{R}\f$
  //! components of the quaternion, respectively.
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
  //!     auto from_cylindrical(auto r, auto angle, auto h1, auto h2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `r`, `angle`, `h1`, `h2`
  //!
  //! **Return value**
  //!
  //! the quaternion value.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/from_cylindrical.cpp}
  //======================================================================================================================
  inline constexpr auto from_cylindrical = eve::functor<from_cylindrical_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}
