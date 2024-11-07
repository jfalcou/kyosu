//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct pow1p_t : eve::strict_elementwise_callable<pow1p_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    -> decltype(kyosu::pow(kyosu::inc(z0), z1))
    { return kyosu::pow(kyosu::inc(z0), z1); }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto  operator()(V0 v0, V1 v1) const noexcept
    -> decltype(eve::pow1p(v0,v1))
    { return eve::pow1p(v0,v1); }

    KYOSU_CALLABLE_OBJECT(pow1p_t, pow1p_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow1p
//!   @brief Computes the  computing the pow1p operation \f$(x+1)^y\f$.
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
//!     constexpr auto average(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      the call is semantically equivalent to `pow(inc(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow1p.cpp}
//======================================================================================================================
  inline constexpr auto pow1p = eve::functor<pow1p_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
