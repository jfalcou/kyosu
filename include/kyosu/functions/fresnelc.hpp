//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sinpi.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct fresnelc_t : eve::elementwise_callable<fresnelc_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      using u_t = underlying_type_t<Z>;
      auto zz = -eve::pi2o_16(eve::as<u_t>())*kyosu::sqr(kyosu::sqr(z)));
      return z*kyosu::hypergeometric(zz, kumi::tuple{u_t(0.25)}, kumi::tuple{u_t(1.25), u_t(0.5)});
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    {
      return (*this)(complex(v));
    }

    KYOSU_CALLABLE_OBJECT(fresnelc_t, fresnelc_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var fresnelc
//!   @brief Computes the Fresnel \f$C\f$ integral \f$\int_0^{\infty} \cos(\frac12 \pi t^2 \;\mathrm{d}t\\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      constexpr T  fresnelc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : real or complex value to process.
//!
//!   **Return value**
//!
//!     Returns the \f$C(z)\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Fresnel Integrals ](https://mathworld.wolfram.com/FresnelIntegrals.html)
//!   *  [Wikipedia: Fresnel integral](https://en.wikipedia.org/wiki/Fresnel_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/fresnelc.cpp}
//======================================================================================================================
  inline constexpr auto fresnelc = eve::functor<fresnelc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
