//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/hypergeometric.hpp>
#include <kyosu/details/hyperg/is_negint.hpp>
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/tgamma_inv.hpp>

namespace kyosu
{
  template<typename Options>
  struct gegenbauer_t : eve::strict_elementwise_callable<gegenbauer_t, Options
                                                         , eve::successor_option, eve::kind_1_option, eve::kind_2_option>
  {
    template<concepts::cayley_dickson_like N, concepts::cayley_dickson_like L, concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<as_cayley_dickson_like_t<N, L, Z>>
    operator()(N nn, L ll, Z zz) const noexcept
    {
      return KYOSU_CALL(nn, ll, zz);
    }

    KYOSU_CALLABLE_OBJECT(gegenbauer_t, gegenbauer_);
  };


//================================================================================================
//! @addtogroup functions
//! @{
//!   @var gegenbauer
//!   @brief Computes the value of the Gegenbauer function of order \f$n\f$
//!
//!   Computes the value of the Gegenbauer function of order \f$n\f$ and parameter
//!   \f$\lambda\f$, \f$C^{(\lambda)}_n(z)\f$ at `z`. If \f$n\f$ is an integer, the function is a
//!   polynomial of degree \f$n\f$.
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
//!   namespace eve
//!   {
//!      // Regular overload
//!      auto constexpr gegenbauer( auto n, auto lambda, auto z)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto gegenbauer[conditional_expr auto c](/* any previous overload */)  noexcept; // 2
//!      constexpr auto gegenbauer[logical_value auto m](/* any previous overload */)     noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`,  lambda, `z` :  real or cayley_dickson.
//!
//!    **Return value**
//!
//!      1.The value of the function at `z` is returned. real input `z` is treated as `complex(z)`.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: GegenbauerC](https://functions.wolfram.com/Polynomials/GegenbauerC3/02/)
//!   *  [Wikipedia: Gegenbauer polynomials](https://en.wikipedia.org/wiki/Gegenbauer_polynomials)
//!   *  [DLMF: Gegenbauer Function](https://dlmf.nist.gov/15.9)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/gegenbauer.cpp}
//================================================================================================
  inline constexpr auto gegenbauer = eve::functor<gegenbauer_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename L, typename N, typename Z>
  EVE_FORCEINLINE constexpr auto gegenbauer_(KYOSU_DELAY(), O const& o,  N nn,  L ll, Z zz) noexcept
  {
    if constexpr(concepts::real<N> && concepts::real<L> && concepts::real<Z>)
    {
      return kyosu::gegenbauer(  nn, ll, complex(zz));
    }
    else
    {
      using r_t = complexify_t<as_cayley_dickson_like_t<N, L, Z>>;
      using u_t = eve::underlying_type_t<r_t>;
      constexpr auto hf = eve::half(eve::as<u_t>());
      auto n = r_t(nn);
      auto l = r_t(ll);
      auto l2 = 2*l;
      auto z = r_t(zz);
      n = if_else(_::is_negint(n+1), eve::next(real(n)), n);
      l = if_else(_::is_negint(l+1), eve::next(real(l)), l);
      auto a = kumi::tuple{-n, n+l2};
      auto b = kumi::tuple{l+hf};
      auto fac = kyosu::tgamma(n+2*l)*kyosu::tgamma_inv(l2)*kyosu::tgamma_inv(n+1);
      auto hyp = hypergeometric(oneminus(z)*hf, a, b);
      auto r = kyosu::if_else(kyosu::is_nan(fac) || is_nan(hyp), kyosu::cinf(eve::as<r_t>()), hyp*fac);
      return r;
    }
  }

  template<eve::conditional_expr C, typename L, typename N, typename Z, eve::callable_options O>
  EVE_FORCEINLINE
  auto gegenbauer_(KYOSU_DELAY(), C cx, O const& o,   N n, L l, Z z) noexcept
  {
    using r_t = complexify_t<as_cayley_dickson_like_t<N, L, Z>>;
    return  eve::detail::mask_op(cx, eve::detail::return_2nd, r_t(z), kyosu::gegenbauer[o]( r_t(n), r_t(l), r_t(z)));
  }
}
