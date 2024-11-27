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
  struct fam_t : eve::strict_elementwise_callable<fam_t, Options>
  {
    template<typename Z0, typename Z1, typename Z2>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1> || concepts::cayley_dickson<Z2>)
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, Z2 const & z2) const noexcept -> decltype(z0+z1+z2)
    { return z0+z1*z2; }

    template<concepts::real V0, concepts::real V1, concepts::real V2>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1, V2 v2) const noexcept -> decltype(v0+v1+v2)
    { return eve::fam(v0,v1,v2); }

    KYOSU_CALLABLE_OBJECT(fam_t, fam_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var fam
//!   @brief  Computes fused add multiply.
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
//!     constexpr auto fam(auto z0, auto z1, auto z2) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`,`z2`: Values to process.
//!
//!   **Return value**
//!
//!    The call is semantically equivalent to `z0+z1*z2`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/fam.cpp}
//======================================================================================================================
  inline constexpr auto fam = eve::functor<fam_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
