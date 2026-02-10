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
  template<typename Options> struct to_multipolar_t : eve::elementwise_callable<to_multipolar_t, Options>
  {
    template<concepts::real V> KYOSU_FORCEINLINE constexpr kumi::tuple<V, V, V, V> operator()(V const& v) const noexcept
    {
      auto z = eve::zero(eve::as(v));
      return kumi::tuple{eve::abs(v), eve::arg(v), z, z};
    }

    template<concepts::cayley_dickson Z>
    requires(dimension_v<Z> <= 4)
    KYOSU_FORCEINLINE constexpr kumi::tuple<as_real_type_t<Z>, as_real_type_t<Z>, as_real_type_t<Z>, as_real_type_t<Z>>
    operator()(Z const& q) const noexcept
    {
      auto c0 = complex(real(q), imag(q));
      if constexpr (kyosu::concepts::complex<Z>)
      {
        auto z = eve::zero(eve::as(abs(c0)));
        return kumi::tuple{abs(c0), arg(c0), z, z};
      }
      else
      {
        auto c1 = complex(jpart(q), kpart(q));
        return kumi::tuple{abs(c0), arg(c0), abs(c1), arg(c1)};
      }
    }

    KYOSU_CALLABLE_OBJECT(to_multipolar_t, to_multipolar_);
  };

  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var to_multipolar
  //!
  //! @brief Callable object computing the multipolar coordinates to a quaternion.
  //!
  //!  This function is the reciprocal of from_multipolar
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
  //!     auto to_multipolar(auto q) const noexcept;
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
  //!   of the multipolar parametrisation of \f$\mathbb{R}^4\f$ coordinates
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/to_multipolar.cpp}
  //================================================================================================
  inline constexpr auto to_multipolar = eve::functor<to_multipolar_t>;
  //================================================================================================
  //!  @}
  //================================================================================================
}
