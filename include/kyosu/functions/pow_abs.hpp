//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/pow.hpp>

namespace kyosu
{
  template<typename Options>
  struct pow_abs_t : eve::strict_elementwise_callable<pow_abs_t, Options>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson Z1>
    requires(!eve::integral_scalar_value<Z1>)
      KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Z1 z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    {
      if constexpr(concepts::real<Z1>)
       return (*this)(z0, complex(z1));
      else
       return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr
      auto operator()(Z0 z0, Z1 z1) const noexcept -> kyosu::as_cayley_dickson_like_t<kyosu::as_real_type_t<Z0>, Z1>
    requires(!eve::integral_scalar_value<Z1>)
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, eve::integral_scalar_value Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Z1 z1) const noexcept -> kyosu::as_real_type_t<Z0>
    {
      return KYOSU_CALL(z0, z1);
    }

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

namespace kyosu::_
{

  template<typename Z0,  typename Z1, eve::callable_options O>
  constexpr auto pow_abs_(KYOSU_DELAY(), O const&, Z0 z0,  Z1 z1) noexcept
  {
    if constexpr(kyosu::concepts::real<Z1> && !eve::integral_value<Z1>)
      return eve::pow(kyosu::sqr_abs(z0), z1*eve::half(eve::as(z1)));
    else
      return kyosu::pow(kyosu::abs(z0), z1);
  }
}
