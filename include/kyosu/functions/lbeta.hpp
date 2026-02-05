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
  template<typename Options> struct lbeta_t : eve::strict_elementwise_callable<lbeta_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const& z1) const noexcept
      -> decltype(kyosu::log[this->options()](kyosu::beta[this->options()](z0, z1)))
    requires(eve::same_lanes_or_scalar<Z0, Z1>)
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::value K>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const& z1, K const& k) const noexcept
      -> eve::as_wide_as_t<decltype(kyosu::log[this->options()](kyosu::beta[this->options()](z0, z1))), K>
    requires(eve::same_lanes_or_scalar<Z0, Z1> && !Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1, k);
    }

    KYOSU_CALLABLE_OBJECT(lbeta_t, lbeta_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var lbeta
  //!   @brief Computes the principal branch of the natural logarithm of the `beta` function.
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
  //!     //  regular call
  //!     auto lbeta(auto z0,auto z1) noexcept;
  //!     auto log(auto z0,  auto z1, eve::value n) noexcept;
  //!
  //!     // semantic modifyers
  //!     auto lbeta[real_only](auto z0, auto z1) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`,`y` : Values to process.
  //!
  //!   **Return value**
  //!
  //!     - Real typed input `z0` and `z1` is treated as if `complex(z0)` and `complex(z1)` were entered,
  //!       unless the option `real_only` is used in which case the  result will the same as to an `eve::lbeta` call
  //!     - Real typed entries are treated as complex ones. unless the option real_only is used
  //!       in which case the parameter must be a floating_value, implying a Nan result if the theoretical result is not
  //!       real.
  //!     - Returns `log(beta(x, y))`.
  //!
  //!  @note lΒ (l followed by upper case greek letter) can be used as an alias in code.
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

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lbeta_(KYOSU_DELAY(), O const& o, Z0 z0, Z1 z1) noexcept
  {
    if constexpr (concepts::real<Z0> && concepts::real<Z1> && O::contains(real_only))
    {
      auto s = eve::signgam(z0) * eve::signgam(z1) * eve::signgam(z0 + z1);
      return eve::if_else(eve::is_gez(s), eve::lbeta(z0, z1), allbits);
    }
    else return kyosu::log[o](kyosu::beta[o](z0, z1));
  }

  template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lbeta_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(z0 + z1))>;
    auto kk = eve::convert(k, as<e_t>());
    return kyosu::lbeta(z0, z1) + muli(kk * two_pi(as(kk)));
  }

  template<concepts::real Z0, concepts::real Z1, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lbeta_(KYOSU_DELAY(), C const& cx, O const& o, Z0 z0, Z1 z1, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z0), lbeta(z0, z1, k...));
  }

}
