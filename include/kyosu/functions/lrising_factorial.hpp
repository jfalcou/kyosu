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
  struct lrising_factorial_t : eve::strict_elementwise_callable<lrising_factorial_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr as_cayley_dickson_t<Z0, Z1> operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return  kyosu::log(rising_factorial(z0, z1)); }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept ->  decltype(eve::lrising_factorial(complex(v0),v1))
    { return eve::lrising_factorial(v0,v1); }

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
//!      auto lrising_factorial(auto x, auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process. Can be a mix of cayley_dickson and real floating values.
//!
//!   **Return value**
//!
//!      \f$\displaystyle \log\left(\frac{\Gamma(a+x)}{\Gamma(a)}\right)\f$ is returned.
//!      If all iputs are real typed they are reated as complex ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lrising_factorial.cpp}
//======================================================================================================================
  inline constexpr auto lrising_factorial = eve::functor<lrising_factorial_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
