//==================================================================================================
/*
  KYOSU - Expressive Vector Engine
  Copyright: KYOSU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/arg.hpp>

namespace kyosu
{
  template<typename Options>
  struct to_cylindrospherical_t : eve::elementwise_callable<to_cylindrospherical_t, Options>
  {
    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr auto operator()(V const& v) const noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{v, z, z, z};
    }

    template<concepts::cayley_dickson Z>
    requires(dimension_v<Z> <= 4)
    KYOSU_FORCEINLINE constexpr auto operator()(Z const& q) const noexcept
    {
      auto q0 = real(q);
      if constexpr(kyosu::concepts::complex<Z>)
      {
        auto z =  eve::zero(eve::as(q0));
        return kumi::tuple{q0, ipart(q), z, z};
      }
      else
      {
        auto lon =  eve::atan2[eve::pedantic](jpart(q), ipart(q));
        auto lat =  eve::atan2[eve::pedantic](kpart(q)*eve::sin(lon),jpart(q));
        return kumi::tuple{q0, abs(pure(q)), lon, lat};
      }
    }

    KYOSU_CALLABLE_OBJECT(to_cylindrospherical_t, to_cylindrospherical_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_cylindrospherical
  //!
  //! @brief Callable object computing the cylindrospherical coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of from_cylindrospherical.
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
  //!     auto to_cylindrospherical(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple containing in this order `t`, `radius`, `longitude` `latitude`:  the components
  //!  of the cylindrospherical parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_cylindrospherical.cpp}
  //================================================================================================
  inline constexpr auto to_cylindrospherical = eve::functor<to_cylindrospherical_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
