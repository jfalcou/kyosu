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
  struct to_spherical_t : eve::elementwise_callable<to_spherical_t, Options>
  {
    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr auto operator()(V const& v) const noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{eve::abs(v), eve::arg(v), z, z};
    }

    template<concepts::cayley_dickson Q>
    requires(dimension_v<Q> <= 4)
      KYOSU_FORCEINLINE constexpr auto operator()(Q  q) const noexcept
    {
      if constexpr(kyosu::concepts::complex<Q>)
      {
        auto c0 = complex(real(q), imag(q));
        auto z =  eve::zero(eve::as(abs(c0)));
        return kumi::tuple{abs(c0), arg(c0), z, z};
      }
      else
      {
        auto rho = kyosu::abs(q);
        auto phi2 = eve::asin(kpart(q)/rho);
        kpart(q) = 0;
        auto rho1 = kyosu::abs(q);
        auto phi1 = eve::asin(jpart(q)/rho1);
        jpart(q) = 0;
        auto rho2 = kyosu::abs(q);
        auto theta= eve::asin(ipart(q)/rho2);
        return kumi::tuple{rho, theta, phi1, phi2};
      }
    }

    KYOSU_CALLABLE_OBJECT(to_spherical_t, to_spherical_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_spherical
  //!
  //! @brief Callable object computing the spherical coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of from_spherical
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
  //!     auto to_spherical(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple containing in this order `rho`, `theta`, `ph1` `ph2`:  the components
  //!  of the spherical parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_spherical.cpp}
  //================================================================================================
  inline constexpr auto to_spherical = eve::functor<to_spherical_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
