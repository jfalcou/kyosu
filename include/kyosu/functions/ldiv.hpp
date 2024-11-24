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
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options>
  struct ldiv_t : eve::strict_elementwise_callable<ldiv_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const & z1) const noexcept -> decltype(z0+z1)
    { return kyosu::rec(z0)*z1; }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept -> decltype(v0+v1)
    { return v1/v0; }

    KYOSU_CALLABLE_OBJECT(ldiv_t, ldiv_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var ldiv
//!   @brief Computes the left division of the two parameters.
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
//!     constexpr auto ldiv(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the left division  of the two arguments. This function not equivalent to z1/z0 as soon as multiplication
//!     is not commutative (i.e. for general Cayley-Dickson values with dimensionality strictly above 2).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/ldiv.cpp}
//======================================================================================================================
  inline constexpr auto ldiv = eve::functor<ldiv_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
