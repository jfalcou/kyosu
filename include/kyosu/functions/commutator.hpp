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
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept -> decltype(z0+z1)
    {
      return KYOSU_CALL(z0,z1);
    }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept -> decltype(v0+v1)
    { return eve::zero(eve::as<decltype(v0+v1)>()); }

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
//!     constexpr auto commutator(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process. Can be a mix of complex and real floating values and complex values.
//!
//!   **Return value**
//!
//!     Returns the difference z0*z1-z1*z0.
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
  template<typename C0, typename C1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto commutator_(KYOSU_DELAY(), O const&, C0 c0, C1 c1) noexcept
  {
    constexpr size_t dC0 = dimension_v<C0>;
    constexpr size_t dC1 = dimension_v<C1>;
    if constexpr((dC0 < 4 && dC1 < 4) || (dC0 == 1 || dC1 == 1))
    {
      return  eve::zero(eve::as<decltype(c0+c1)>());
    }
    else
    {
      return c0*c1 - c1*c0;
    }
  }
}
