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
  struct pow1p_t : eve::strict_elementwise_callable<pow1p_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr
    auto  operator()(Z0 z0, Z1 z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    requires(!eve::integral_scalar_value<Z1> && !Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, eve::integral_scalar_value Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Z1 z1) const noexcept-> complexify_t<Z0>
    requires(!Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::real Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 const& z0, Z1 const& z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    requires(Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1);
    }

    KYOSU_CALLABLE_OBJECT(pow1p_t, pow1p_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow1p
//!   @brief Computes the pow1p operation \f$(x+1)^y\f$.
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
//!     constexpr auto pow1p[real_only](auto z0, auto z1) noexcept;
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
    if constexpr(O::contains(real_only))
      return kyosu::inject(eve::pow1p(z0, z1));
    else if constexpr(concepts::real<Z0> && concepts::real<Z1>)
    {
      using s_t = kyosu::as_cayley_dickson_like_t<Z0, Z1>;
      s_t zz0(z0);
      s_t z0p1(eve::inc(zz0));
      s_t zz1(z1);
      return kyosu::if_else(eve::is_gez(z0p1),  complex(eve::pow1p(zz0, zz1)), exp_ipi(zz1)*eve::pow(-z0p1, zz1));
    }
    else
      return kyosu::pow(kyosu::inc(z0), z1);
  }
}
