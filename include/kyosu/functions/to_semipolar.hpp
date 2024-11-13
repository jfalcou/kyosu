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

    template<concepts::cayley_dickson Z>
    requires(dimension_v<Q> <= 4)
      KYOSU_FORCEINLINE constexpr auto operator()(Z  q) const noexcept
    {
      auto c0 = complex(real(q), imag(q));
      if constexpr(kyosu::concepts::complex<Z>)
      {
        auto z =  eve::zero(eve::as(abs(c0)));
        return kumi::tuple{abs(c0), z, arg(c0), z};
      }
      else
      {
        auto rho = kyosu::abs(q);
        auto c0 = complex(get<0>(q), get<1>(q));
        auto c1 = complex(get<2>(q), get<3>(q));
        auto alpha = eve::pedantic(eve::atan2)(abs(c1), abs(c0));
        auto theta1 = arg(c0);
        auto theta2 = arg(c1);
        return kumi::tuple{rho, alpha, theta1, theta2};
      }
    }

    KYOSU_CALLABLE_OBJECT(to_spherical_t, to_spherical_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_semipolar
  //!
  //! @brief Callable object computing the semipolar coordinates from a quaternion.
  //!
  //!  This function is the reciprocal of from_semipolar
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
  //!     auto to_semipolar(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion
  //!
  //! **Return value**
  //!
  //!  a tuple containing in this order `rho1`, `theta1`, `h1` `h2`:  the components
  //!  of the semipolar parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/to_semipolar.cpp}
  //================================================================================================
  inline constexpr auto to_spherical = eve::functor<to_spherical_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
