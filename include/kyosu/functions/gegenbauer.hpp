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
#include <kyosu/functions/hyperg/is_negint.hpp>
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/tgamma_inv.hpp>

namespace kyosu
{
  template<typename Options>
  struct gegenbauer_t : eve::strict_elementwise_callable<gegenbauer_t, Options
                                                         , eve::successor_option, eve::kind_1_option, eve::kind_2_option>
  {
    template<concepts::cayley_dickson N, concepts::cayley_dickson L, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N nn, L ll, Z zz) const noexcept -> decltype(nn+ll+zz)
    {
      using r_t = decltype(nn+zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto n = r_t(nn);
      auto l = r_t(ll);
      auto l2 = 2*l;
      auto z = r_t(zz);
      n = if_else(is_negint(n+1), eve::next(real(n)), n);
      l = if_else(is_negint(l1+1), eve::next(real(l)), l);
      auto hf = eve::half(eve::as<u_t>());
      auto fac = kyosu::tgamma(n+2*l)*kyosu::tgamma_inv(l2)*kyosu::tgamma_inv(n+1);
      auto r = kyosu::inc(n)*hypergeometric(oneminus(z)*hf), kumi::tuple{-n, n+l2}, kumi::tuple{l+hf});
    }

    template<concepts::real N, concepts::real N, concepts::real Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N n,, L ll, Z z) const noexcept -> decltype(n+l+complex(z))
    { return (*this)(n, l, complex(z)); }


    KYOSU_CALLABLE_OBJECT(gegenbauer_t, gegenbauer_);
  };


//================================================================================================
//! @addtogroup functions
//! @{
//!   @var gegenbauer
//!   @brief Computes the value of the Gegenbauer function of order \f$n\f$ and parameter  \f$\lambda\f$,  \f$C^{(\lambda)}_n(z)\f$ at `z`.
//!     If \f$n\f$ is an integer the function is a polynomial of degree \f$n\f$.
//!
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
//!      auto constexpr gegenbauer( auto n, auto lambda, auto z) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto gegenbauer[conditional_expr auto c](/* any previous overload */)                 noexcept; // 2
//!      constexpr auto gegenbauer[logical_value auto m](/* any previous overload */)                    noexcept; // 2
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`,  lambda, `z` :  real or cayley_dickson. 
//!
//!    **Return value**
//!
//!      1.The value of the function at `z` is returned.
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
