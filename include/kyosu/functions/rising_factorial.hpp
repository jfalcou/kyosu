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
  struct rising_factorial_t : eve::strict_elementwise_callable<rising_factorial_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_t<Z0, Z1> operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return kyosu::if_else(is_eqz(z1), one, tgamma(z0+z1)/tgamma(z0));; }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept ->  decltype(eve::rising_factorial(complex(v0),v1))
    { return eve::rising_factorial(v0,v1); }

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
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/rising_factorial.cpp}
//======================================================================================================================
  inline constexpr auto rising_factorial = eve::functor<rising_factorial_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
