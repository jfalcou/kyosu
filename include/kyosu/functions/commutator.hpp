//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct commutator_t : eve::strict_elementwise_callable<commutator_t, Options, pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    requires(eve::same_lanes_or_scalar<Z0, Z1>)
      KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<Z0, Z1> operator()(Z0 const& z0, Z1 const & z1) const
      noexcept
    {
      return  KYOSU_CALL(z0, z1);
    }

    KYOSU_CALLABLE_OBJECT(commutator_t, commutator_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var commutator
//!   @brief Computes the commutator of the two parameters.
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
//!     constexpr auto commutator(auto z0, auto z1)           noexcept; //1
//!     constexpr auto commutator[pedantic](auto z0, auto z1) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process. Can be a mix of cayley_dickson_like values.
//!
//!   **Return value**
//!
//!     1. Returns the difference z0*z1-z1*z0. (always exactly zero up to complex)
//!     2. Always computes the result that can sometimes be a NaN.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Commutator](https://mathworld.wolfram.com/Commutator.html)
//!   *  [Wikipedia: Commutator](https://en.wikipedia.org/wiki/Commutator)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/commutator.cpp}
//======================================================================================================================
  inline constexpr auto commutator = eve::functor<commutator_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto commutator_(KYOSU_DELAY(), O const&, Z0 z0, Z1 const & z1) noexcept
  {
    if constexpr(!O::contains(pedantic) && (concepts::complex_like<Z0> && concepts::complex_like<Z1>) ||
                 (concepts::real<Z0> || concepts::real<Z1>))
      return  eve::zero(eve::as<as_cayley_dickson_like_t<Z0, Z1>>());
    else
      return (z0*z1) - (z1*z0);
  }
}
