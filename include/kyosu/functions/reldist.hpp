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
  struct reldist_t : eve::strict_elementwise_callable<reldist_t, Options, eve::pedantic_option, eve::numeric_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 z0, Z1 z1) const noexcept -> decltype(kyosu::dist(z0, z1))
    {
      return KYOSU_CALL(z0, z1);
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
//!     // regular call
//!     constexpr auto reldist(auto z0, auto z1) noexcept;           //1
//!
//!     // Semantic modifyiers
//!     constexpr auto reldist[pedantic](auto z0, auto z1) noexcept; //2
//!     constexpr auto reldist[numeric](auto z0, auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Value to process.
//!
//!   **Return value**
//!
//!      1. Returns the the relative distance computed as the absolute value of the arguments difference given by `dist`
//!        divided by the maximum of their absolute values and 1.
//!      2. if the pedantic option is used the distance betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic and also return zero if all corresponding parts satisfy `eve::is_equal[numeric]`.
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
namespace kyosu::_
{
  template<typename C0,  typename C1, eve::callable_options O>
  constexpr auto reldist_(KYOSU_DELAY(), O const& o, C0 c0,  C1 c1) noexcept
  {
    auto d = dist[o](c0, c1);
    return if_else( is_infinite(d) || is_eqz(d), d, d/eve::max(kyosu::abs(c0), kyosu::abs(c1), eve::one(eve::as(abs(c0)))));
  }
}
