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
    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...> {};

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, concepts::cayley_dickson_like Z2>
    requires(eve::same_lanes_or_scalar<Z0, Z1, Z2>)
    KYOSU_FORCEINLINE constexpr typename result<Z0,Z1,Z2>::type
    operator()(Z0 const& c0, Z1 const & c1, Z2 const & c2) const noexcept
    {
      return KYOSU_CALL(c0, c1, c2);
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

namespace kyosu::_
{
  template<typename C0, typename C1, typename C2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto associator_(KYOSU_DELAY(), O const&, C0 c0, C1 c1, C2 c2) noexcept
  {
    if constexpr(O::contains(eve::pedantic))
      return (c0*c1)*c2 - c0*(c1*c2);
    else
    {
      if constexpr((concepts::quaternion_like<C0> && concepts::quaternion_like<C1> && concepts::quaternion_like<C2>) ||
                   concepts::real<C0> || concepts::real<C1> || concepts::real<C2>)
        return zero(kyosu::as<decltype( (c0*c1)*c2 - c0*(c1*c2))>());
      else
        return (c0*c1)*c2 - c0*(c1*c2);
    }
  }
}
