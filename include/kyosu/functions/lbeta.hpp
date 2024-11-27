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
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/beta.hpp>

namespace kyosu
{
  template<typename Options>
  struct lbeta_t : eve::strict_elementwise_callable<lbeta_t, Options>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr as_cayley_dickson_t<Z0, Z1>  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return kyosu::log(kyosu::beta(z0, z1)); }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept -> decltype(complex(v0)+v1)
    { return (*this)(complex(v0),v1); }

    KYOSU_CALLABLE_OBJECT(lbeta_t, lbeta_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lbeta
//!   @brief Computes the natural logarithm of the `beta` function.
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
//!      auto lbeta(auto x,auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,`y` : Values to process.
//!
//!   **Return value**
//!
//!    `log(beta(x, y))`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lbeta.cpp}
//======================================================================================================================
  inline constexpr auto lbeta = eve::functor<lbeta_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
