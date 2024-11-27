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
  struct powm1_t : eve::strict_elementwise_callable<powm1_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    -> decltype(kyosu::dec(kyosu::pow(z0, z1)))
    { return kyosu::dec(kyosu::pow(z0, z1)); }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    -> decltype(eve::powm1(v0,v1))
    { return eve::powm1(v0,v1); }

    KYOSU_CALLABLE_OBJECT(powm1_t, powm1_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var powm1
//!   @brief Computes the  computing the powm1 operation \f$x^y-1\f$.
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
//!     constexpr auto powm1(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `dec(pow(z0, z1))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/powm1.cpp}
//======================================================================================================================
  inline constexpr auto powm1 = eve::functor<powm1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
