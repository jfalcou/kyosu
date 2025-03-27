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
  struct powm1_t : eve::strict_elementwise_callable<powm1_t, Options>
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

    KYOSU_CALLABLE_OBJECT(powm1_t, powm1_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var powm1
//!   @brief Computes the  computing the powm1 operation \f$x^y-1\f$.
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
//!     constexpr auto powm1(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `dec(pow(z0, z1))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/powm1.cpp}
//======================================================================================================================
  inline constexpr auto powm1 = eve::functor<powm1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z0,  typename Z1, eve::callable_options O>
  constexpr auto powm1_(KYOSU_DELAY(), O const&, Z0 z0,  Z1 z1) noexcept
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1>)
      return kyosu::dec(kyosu::pow(complex(z0),z1));
    else
      return kyosu::dec(kyosu::pow(z0, z1));
  }
}
