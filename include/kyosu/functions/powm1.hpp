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
  struct powm1_t : eve::strict_elementwise_callable<powm1_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr
    auto  operator()(Z0 z0, Z1 z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    requires(!eve::integral_scalar_value<Z1> && !Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, eve::integral_value Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Z1 z1) const noexcept  -> eve::as_wide_as_t<Z0, Z1>
    requires(!Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::real Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 const& z0, Z1 const& z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    requires(Options::contains(real_only))
    {
      auto r = eve::powm1(z0, z1);
      return complex(r, eve::if_else(eve::is_nan(r), eve::nan, eve::zero(as(r))));
    }

    template<concepts::real Z0, eve::integral_value Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 const& z0, Z1 const& z1) const noexcept -> complexify_t<eve::as_wide_as_t<Z0, Z1>>
    requires(Options::contains(real_only))
    {
      auto r = eve::powm1(z0, z1);
      return complex(r, eve::if_else(eve::is_nan(r), eve::nan, eve::zero(as(r))));
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
      return kyosu::if_else(eve::is_gez(z0),  complex(eve::powm1(z0, z1)), kyosu::dec(exp_ipi(z1)*eve::pow(-z0, z1)));
    else
      return kyosu::dec(kyosu::pow(z0, z1));
  }
}
