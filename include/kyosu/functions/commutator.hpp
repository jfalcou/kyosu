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
  struct commutator_t : eve::strict_elementwise_callable<commutator_t, Options>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    requires(eve::same_lanes_or_scalar<Z0, Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const
      noexcept -> decltype(z0+z1)
    {
      constexpr size_t dZ0 = dimension_v<Z0>;
      constexpr size_t dZ1 = dimension_v<Z1>;
      if constexpr((concepts::complex_like<Z0> && concepts::complex_like<Z1>) ||
                   (concepts::real<Z0> || concepts::real<Z1>))
        return  eve::zero(eve::as<decltype(z0+z1)>());
      else
        return (z0*z1) - (z1*z0);
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
//!     constexpr auto commutator(auto z0, auto z1)           noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process. Can be a mix of cayley_dickson_like values.
//!
//!   **Return value**
//!
//!     Returns the difference z0*z1-z1*z0. (always exactly zero up to complex)
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
