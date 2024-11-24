//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/pow.hpp>

namespace kyosu
{
  template<typename Options>
  struct pow_abs_t : eve::strict_elementwise_callable<pow_abs_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept  -> decltype(abs(z0)+z1)
    {
      if constexpr(kyosu::concepts::real<Z1>)
        return eve::pow(kyosu::sqr_abs(z0), z1*eve::half(eve::as(z1)));
      else
        return kyosu::pow(abs(z0), z1);
    }

    template<concepts::real V0, concepts::real V1>
    requires(!eve::integral_value<V1>)
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept -> decltype(v0+v1)
    { return eve::pow_abs(v0,v1); }

    template<typename V0, eve::integral_value V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept -> decltype(kyosu::abs(v0)+v1)
    { return eve::pow(kyosu::abs(v0),v1); }

    KYOSU_CALLABLE_OBJECT(pow_abs_t, pow_abs_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow_abs
//!   @brief Computes the  computing the pow_abs operation \f$|x|^y\f$.
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
//!     constexpr auto pow_abs(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `kyosu::exp(log_abs(z0)*z1)` In particular if z1 is floating typed the
//!      result is floating_typed, which is not the case of kyosu::pow(abs(z0), z1);
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow_abs.cpp}
//======================================================================================================================
  inline constexpr auto pow_abs = eve::functor<pow_abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
