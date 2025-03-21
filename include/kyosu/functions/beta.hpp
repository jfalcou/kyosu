//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/tgamma.hpp>

namespace kyosu
{
  template<typename Options>
  struct beta_t : eve::strict_elementwise_callable<beta_t, Options>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr auto
    operator()(Z0 const& z0, Z1 const & z1) const noexcept -> decltype(complex(z0)+complex(z1))
    {
      if constexpr(eve::floating_value<Z0>, eve::floating_value<Z1>)
        return (*this)(complex(z0), complex(z1));
      else
      {
        auto y = z0 + z1;
        return tgamma(z0)*tgamma(z1)/tgamma(y);
      }
    }

    KYOSU_CALLABLE_OBJECT(beta_t, beta_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var beta
//!   @brief Computes the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$
//!   for real or complex entries.
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
//!      auto beta(auto x, auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process. Can be a mix of Cayley_dickson and real floating values.
//!
//!   **Return value**
//!
//!      \f$\displaystyle  \mathbf{B}(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
//!     If  `x` and `y` are real typed values they are treated as complex inputs.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Beta Function](https://mathworld.wolfram.com/BetaFunction.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/beta.cpp}
//======================================================================================================================
  inline constexpr auto beta = eve::functor<beta_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
