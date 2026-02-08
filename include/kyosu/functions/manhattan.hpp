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
  struct manhattan_t
    : eve::strict_tuple_callable<manhattan_t, Options, eve::saturated_option, eve::pedantic_option, eve::kahan_option>
  {

    template<concepts::cayley_dickson_like... Zs>
    KYOSU_FORCEINLINE constexpr auto operator()(Zs... zs) const noexcept -> decltype(eve::manhattan(real(zs)...))
    {
      return KYOSU_CALL(zs...);
    }

    KYOSU_CALLABLE_OBJECT(manhattan_t, manhattan_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var manhattan
  //!   @brief Computes the sum of the absolute values of all terms of all the parameters.
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
  //!      // Regular overloads
  //!      constexpr auto manhattan(auto ... xs)                                              noexcept; // 1
  //!      constexpr auto manhattan(eve::non_empty_product_type auto const& tup)             noexcept; // 2
  //!
  //!      // Lanes masking
  //!      constexpr auto manhattan[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
  //!      constexpr auto manhattan[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
  //!      constexpr auto manhattan[saturated](/*any of the above overloads*/)                noexcept; // 4
  //!      constexpr auto manhattan[pedantic](/*any of the above overloads*/)                 noexcept; // 5
  //!      constexpr auto manhattan[kahan](/*any of the above overloads*/)                    noexcept; // 6
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `xs...`: Values to process.
  //!
  //!   **Return value**
  //!
  //!     1. The value of the sum of the values (the\f$l_1\f$ norm) of the \f$l_1\f$ norm of its arguments is returned.
  //!     2. same as 1. on the tuple elements.
  //!     3. [The operation is performed conditionnaly](@ref conditional)
  //!     4. internally uses `saturated` options.
  //!     5. returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
  //!     6. uses kahan like compensated algorithm for better accuracy.
  //!
  //!  @note This is NOT `lpnorm(1, x0, xs...)` which is the \f$l_1\f$ norm of \f$l_2\f$ norm of its arguments.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: L1 norm](https://mathworld.wolfram.com/L1-Norm.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/manhattan.cpp}
  //======================================================================================================================
  inline constexpr auto manhattan = eve::functor<manhattan_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename... Zs>
  KYOSU_FORCEINLINE constexpr auto manhattan_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    if constexpr (concepts::real<Z0> && (... && concepts::real<Zs>)) return eve::manhattan[o](z0, zs...);
    else return eve::manhattan[o](kumi::flatten(kumi::make_tuple(z0, zs...)));
  }
}
