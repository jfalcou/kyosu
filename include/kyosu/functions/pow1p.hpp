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

namespace kyosu
{
  template<typename Options>
  struct pow1p_t : eve::strict_elementwise_callable<pow1p_t, Options>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    requires(!eve::integral_scalar_value<Z1>)
    KYOSU_FORCEINLINE constexpr
    auto  operator()(Z0 z0, Z1 z1) const noexcept //complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, eve::integral_value Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Z1 z1) const noexcept //-> decltype(z0+z1)
    {
      return KYOSU_CALL(z0, z1);
    }

    KYOSU_CALLABLE_OBJECT(pow1p_t, pow1p_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow1p
//!   @brief Computes the  computing the pow1p operation \f$(x+1)^y\f$.
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
//!     constexpr auto pow1p(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `pow(inc(z0), z1)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow1p.cpp}
//======================================================================================================================
  inline constexpr auto pow1p = eve::functor<pow1p_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z0,  typename Z1, eve::callable_options O>
  constexpr auto pow1p_(KYOSU_DELAY(), O const&, Z0 z0,  Z1 z1) noexcept
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1>)
    {
      auto z0p1 = eve::inc(z0);
      return kyosu::if_else(eve::is_gez(z0p1),  complex(eve::pow1p(z0, z1)), exp_ipi(z1)*eve::pow(-z0p1, z1));
    }
    else
      return kyosu::pow(kyosu::inc(z0), z1);
  }
}
