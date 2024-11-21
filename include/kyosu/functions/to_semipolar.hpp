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
  struct to_semipolar_t : eve::elementwise_callable<to_semipolar_t, Options>
  {
    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr auto operator()(V const& v) const noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{eve::abs(v), eve::arg(v), z, z};
    }

    template<concepts::cayley_dickson Z>
    requires(dimension_v<Z> <= 4)
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
        auto alpha = eve::atan2[eve::pedantic](abs(c1), abs(c0));
        auto theta1 = arg(c0);
        auto theta2 = arg(c1);
        return kumi::tuple{rho, alpha, theta1, theta2};
      }
    }

    KYOSU_CALLABLE_OBJECT(to_semipolar_t, to_semipolar_);
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
  //! @groupheader{Header file}
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
  inline constexpr auto to_semipolar = eve::functor<to_semipolar_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
