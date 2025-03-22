//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct associator_t : eve::strict_elementwise_callable<associator_t, Options, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, concepts::cayley_dickson_like Z2>
    requires(eve::same_lanes_or_scalar<Z0, Z1, Z2>)
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& c0, Z1 const & c1, Z2 const & c2) const
      noexcept -> decltype(c0+c1+c2)
    {
      if constexpr(Options::contains(eve::pedantic))
        return (c0*c1)*c2 - c0*(c1*c2);
      else
      {
        if constexpr((concepts::quaternion_like<Z0> && concepts::quaternion_like<Z1> && concepts::quaternion_like<Z2>) ||
                     concepts::real<Z0> || concepts::real<Z1> || concepts::real<Z2>)
          return zero(as<decltype(c0+c1+c2)>());
        else
          return (c0*c1)*c2 - c0*(c1*c2);
      }
    }

    KYOSU_CALLABLE_OBJECT(associator_t, associator_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var associator
//!   @brief Computes the associator of the three parameters.
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
//!     Regular call
//!     constexpr auto associator(auto z0, auto z1, auto z2) noexcept;           //1
//!
//!     Semantic modifyier
//!     constexpr auto associator[pedantic](auto z0, auto z1, auto z2) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, `z2`: Values to process. (Can be a mix of cayley-dickson and real floating values).
//!
//!   **Return value**
//!
//!     1.  Returns the difference z0*(z1*z2)-(z0*z1)*z2. (always exactly zero up to quaternion)
//!     2.  Same,  but always do the computation. (up to quaternions, non zero result is merely the
//!         floating point associativity rounding error)
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Associator](https://en.wikipedia.org/wiki/Associator)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/associator.cpp}
//======================================================================================================================
  inline constexpr auto associator = eve::functor<associator_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
