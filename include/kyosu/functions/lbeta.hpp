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
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/beta.hpp>

namespace kyosu
{
  template<typename Options>
  struct lbeta_t : eve::strict_elementwise_callable<lbeta_t, Options>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_t<complexify_t<Z0>, complexify_t<Z1>>
    operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return kyosu::log(kyosu::beta(z0, z1)); }

    KYOSU_CALLABLE_OBJECT(lbeta_t, lbeta_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lbeta
//!   @brief Computes the natural logarithm of the `beta` function.
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
//!      auto lbeta(auto x,auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!    `log(beta(x, y))`.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Beta Function](https://mathworld.wolfram.com/BetaFunction.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/lbeta.cpp}
//======================================================================================================================
  inline constexpr auto lbeta = eve::functor<lbeta_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
