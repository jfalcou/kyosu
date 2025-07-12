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
      KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const & z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    requires(!Options::contains(real_only))
    {
      return KYOSU_CALL(z0, z1);
    }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept ->  complexify_t<kyosu::as_cayley_dickson_like_t<V0, V1>>
    requires(!Options::contains(real_only))
    {
      return KYOSU_CALL(v0, v1);
    }

    template<concepts::real Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const& z1) const noexcept -> complexify_t<kyosu::as_cayley_dickson_like_t<Z0, Z1>>
    requires(Options::contains(real_only))
    {
       return KYOSU_CALL(z0, z1);
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
//!     auto lrising_factorial[real_only](auto z) noexcept;
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
//!     - Real typed entries are treated as complex ones. unless the option real_only is used
//!       in which case the parameter must be a floating_value,  the real part of the result will the same as an eve::lrising_factorial
//!       implying a Nan result if the result is not real.
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
  template<typename Z0,  typename Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lrising_factorial_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1) noexcept
  {
    if constexpr(O::contains(kyosu::real_only))
      return kyosu::inject(eve::lrising_factorial(z0, z1));
    if constexpr(kyosu::concepts::complex_like<Z0> && kyosu::concepts::complex_like<Z1>)
    {
      return kyosu::log(kyosu::rising_factorial(z0, z1));
    }
    else return kyosu::_::cayley_extend2(kyosu::lrising_factorial, z0, z1);
  }
}
