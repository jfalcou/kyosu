//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>
#include <kyosu/functions/dist.hpp>
#include <kyosu/functions/is_eqz.hpp>
#include <kyosu/functions/is_nan.hpp>

namespace kyosu
{
  template<typename Options>
  struct reldist_t : eve::strict_elementwise_callable<reldist_t, Options, eve::numeric_option>
  {
    template<typename Z0, typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept -> decltype(kyosu::dist(c0, c1))
    {
      auto d = dist(c0, c1);
      auto r = d/eve::max(kyosu::abs(c0), kyosu::abs(c1), eve::one(eve::as(abs(c0))));
      if (Options::contains(eve::numeric))
      {
        return if_else (kyosu::is_eqz(c0-c1) || (kyosu::is_nan(c0) && kyosu::is_nan(c1)),  zero,  r);
      }
      else
      {
        return r;
      }
    }

    template<concepts::real Z0, concepts::real Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept -> decltype(eve::reldist(c0,c1))
    {
      auto d = dist(c0, c1);
      auto r = d/eve::max(kyosu::abs(c0), kyosu::abs(c1), eve::one(eve::as(abs(c0))));
      if (Options::contains(eve::numeric))
      {
        return if_else (is_eqz(d) || (is_nan(c0) && is_nan(c1)),  zero,  r);
      }
      else
      {
        return r;
      }
    }

    KYOSU_CALLABLE_OBJECT(reldist_t, reldist_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var reldist
//!   @brief Computes the relative distance between the two parameters.
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
//!     constexpr auto reldist(auto z0, auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the the relative distance computed as the absolute value of the arguments difference
//!     divided by the maximum of their absolute values and 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/reldist.cpp}
//======================================================================================================================
  inline constexpr auto reldist = eve::functor<reldist_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
