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
#include <kyosu/functions/rising_factorial.hpp>

namespace kyosu
{
  template<typename Options>
  struct lrising_factorial_t : eve::strict_elementwise_callable<lrising_factorial_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    -> decltype(kyosu::log[this->options()](kyosu::rising_factorial[this->options()](z0, z1)))
      requires(eve::same_lanes_or_scalar<Z0, Z1>)
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::value K>
    KYOSU_FORCEINLINE constexpr auto
    operator()(Z0 const& z0, Z1 const & z1, K const & k) const noexcept
    -> eve::as_wide_as_t<decltype(kyosu::log[this->options()](kyosu::rising_factorial[this->options()](z0, z1))), K>
    requires(eve::same_lanes_or_scalar<Z0, Z1> && !Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1, k);
    }

    KYOSU_CALLABLE_OBJECT(lrising_factorial_t, lrising_factorial_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lrising_factorial
//!   @brief Computes the natural logarithm of the rising_factorial function
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
//!     auto lrising_factorial(auto x,auto y) noexcept;
//!
//!     // semantic modifyers
//!     auto lrising_factorial[real_only](auto x,auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process. Can be a mix of cayley_dickson and real floating values.
//!
//!   **Return value**
//!
//!     - \f$\displaystyle \log\left(\frac{\Gamma(a+x)}{\Gamma(a)}\right)\f$ is returned.
//!     - Real typed entries are treated as complex ones, unless the option real_only is used
//!       in which case the parameters must be floating values,  implying a Nan result if the result is not real.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Rising Factorial](https://mathworld.wolfram.com/RisingFactorial.html)
//!   *  [Wikipedia: Error Function](https://en.wikipedia.org/wiki/Falling_and_rising_factorials)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/lrising_factorial.cpp}
//======================================================================================================================
  inline constexpr auto lrising_factorial = eve::functor<lrising_factorial_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lrising_factorial_(KYOSU_DELAY(), O const& o, Z0 z0, Z1 z1) noexcept
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1> && O::contains(real_only))
    {
      return eve::lrising_factorial[eve::pedantic](z0, z1);
    }
   else
      return kyosu::log[o](kyosu::rising_factorial[o](z0, z1));
  }

  template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lrising_factorial_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(z0+z1))>;
    auto kk = eve::convert(k, as<e_t>());
    return kyosu::lrising_factorial(z0, z1)+muli(kk*two_pi(as(kk)));
  }

  template<concepts::real Z0, concepts::real Z1, eve::value ...K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lrising_factorial_(KYOSU_DELAY(), C const& cx, O const& o, Z0 z0, Z1 z1, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z0), lrising_factorial(z0, z1, k...));
  }
}
