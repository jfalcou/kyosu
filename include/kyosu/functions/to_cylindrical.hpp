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
  struct to_cylindrical_t : eve::elementwise_callable<to_cylindrical_t, Options>
  {
    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr auto operator()(V const& v) const noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{eve::abs(v), eve::arg(v), z, z};
    }

    template<concepts::cayley_dickson Q>
    requires(dimension_v<Q> <= 4)
    KYOSU_FORCEINLINE constexpr auto operator()(Q const& q) const noexcept
    {
      auto c0 = complex(real(q), imag(q));
      if constexpr(kyosu::concepts::complex<Q>)
      {
        auto z =  eve::zero(eve::as(abs(c0)));
        return kumi::tuple{abs(c0), arg(c0), z, z};
      }
      else
      {
        return kumi::tuple{abs(c0), arg(c0), jpart(q), kpart(q) };
      }
    }

    KYOSU_CALLABLE_OBJECT(to_cylindrical_t, to_cylindrical_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_cylindrical
  //!
  //! @brief Callable object computing the cylindrical coordinates to a quaternion.
  //!
  //!  This function is the reciprocal of `from_cylindrical`
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
  //!     auto to_cylindrical(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  `q`: quaternion
  //!
  //! **Return value**
  //!
  //!   a tuple containing in this order `rho1`, `theta1`, `h1`, `h2`:  the components
  //!   of the cylindrical parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/to_cylindrical.cpp}
  //================================================================================================
  inline constexpr auto to_cylindrical = eve::functor<to_cylindrical_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
