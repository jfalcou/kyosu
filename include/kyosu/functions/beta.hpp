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
  struct beta_t : eve::strict_elementwise_callable<beta_t, Options, real_only_option>
  {
    template<typename T0, typename T1>                                           struct result;
    template<concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1> struct result<T0, T1> : as_cayley_dickson<T0, T1> {};
    template<concepts::real T0, concepts::real T1>                               struct result<T0, T1> : eve::common_value<T0, T1> {};

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr
    complexify_if_t<Options, typename result<Z0, Z1>::type> operator()(Z0 const& z0, Z1 const & z1) const noexcept
    requires(eve::same_lanes_or_scalar<Z0, Z1>)
    {
      return KYOSU_CALL(z0, z1);
    }

    KYOSU_CALLABLE_OBJECT(beta_t, beta_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var beta
//!   @brief Computes the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$
//!   for real, complex or general Cayley_dickson entries.
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
//!  @note Β (upper case greek letter) can be used as an alias in code.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Beta Function](https://mathworld.wolfram.com/BetaFunction.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/beta.cpp}
//======================================================================================================================
  inline constexpr auto beta = eve::functor<beta_t>;
  inline constexpr auto Β = eve::functor<beta_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto beta_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1) noexcept
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1>)
    {
      if constexpr(O::contains(real_only))
        return eve::beta(z0, z1);
      else
        return kyosu::beta(complex(z0), complex(z1));
    }
    else if constexpr(kyosu::concepts::complex_like<Z0> && kyosu::concepts::complex_like<Z1>)
      return tgamma(z0)*tgamma(z1)/tgamma( z0 + z1);
    else
      return kyosu::_::cayley_extend(tgamma, z0)*kyosu::_::cayley_extend(tgamma, z1)/kyosu::_::cayley_extend(tgamma, z0+z1);
  }

  template<concepts::real Z0, concepts::real Z1, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto beta_(KYOSU_DELAY(), C const& cx, O const&, Z0 z0, Z1 z1) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z0), beta(z0, z1));
  }

}
