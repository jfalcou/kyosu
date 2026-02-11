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
#include <kyosu/functions/tgamma_inv.hpp>

namespace kyosu
{
  template<typename Options>
  struct rising_factorial_t : eve::strict_elementwise_callable<rising_factorial_t, Options, real_only_option>
  {
    template<typename T0, typename T1> struct result;
    template<concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1>
    struct result<T0, T1> : as_cayley_dickson<T0, T1>
    {
    };
    template<concepts::real T0, concepts::real T1> struct result<T0, T1> : eve::common_value<T0, T1>
    {
    };

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, typename result<Z0, Z1>::type> operator()(
      Z0 const& z0, Z1 const& z1) const noexcept
    requires(eve::same_lanes_or_scalar<Z0, Z1>)
    {
      return KYOSU_CALL(z0, z1);
    }

    KYOSU_CALLABLE_OBJECT(rising_factorial_t, rising_factorial_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var rising_factorial
  //!   @brief Computes the rising_factorial function: \f$\displaystyle \frac{\Gamma(a+x)}{\Gamma(a)}\f$
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
  //!      auto rising_factorial(auto x, auto y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`,`y` : Values to process. Can be a mix of cayley_dickson and real floating values.
  //!
  //!   **Return value**
  //!
  //!      \f$\displaystyle \frac{\Gamma(a+x)}{\Gamma(a)}\f$ is returned.
  //!     If  `x` and `y` are real typed values they are treated as complex inputs unless the option `real_only` is used
  //!     in which case the  result will the same as to an `eve::rising_factorial` call
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Rising Factorial](https://mathworld.wolfram.com/RisingFactorial.html)
  //!   *  [Wikipedia: Error Function](https://en.wikipedia.org/wiki/Falling_and_rising_factorials)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/rising_factorial.cpp}
  //======================================================================================================================
  inline constexpr auto rising_factorial = eve::functor<rising_factorial_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto rising_factorial_(KYOSU_DELAY(), O const&, Z0 z0, Z1 z1) noexcept
  {
    if constexpr (concepts::real<Z0> && concepts::real<Z1> && O::contains(real_only))
    {
      return eve::rising_factorial(z0, z1);
    }
    else if constexpr (kyosu::concepts::complex_like<Z0> && kyosu::concepts::complex_like<Z1>)
    {
      auto zz0 = complex(z0);
      return kyosu::if_else(is_eqz(z1), one, tgamma(zz0 + z1) * tgamma_inv(zz0));
    }
    else return kyosu::_::cayley_extend(tgamma, z0 + z1) * kyosu::_::cayley_extend(tgamma_inv, z0);
  }

  template<concepts::real Z0, concepts::real Z1, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto rising_factorial_(KYOSU_DELAY(), C const& cx, O const&, Z0 z0, Z1 z1) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z0), rising_factorial(z0, z1));
  }

}
