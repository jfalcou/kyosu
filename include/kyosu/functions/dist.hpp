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
  struct dist_t : eve::strict_elementwise_callable<dist_t, Options, eve::pedantic_option, eve::numeric_option>
  {
   template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1 >
    KYOSU_FORCEINLINE constexpr as_real_type_t<as_cayley_dickson_like_t<Z0, Z1>> operator()(Z0 c0, Z1 c1) const noexcept
    {
      return KYOSU_CALL(c0, c1);
    }

    KYOSU_CALLABLE_OBJECT(dist_t, dist_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dist
//!   @brief Computes the distance between the two parameters.
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
//!     constexpr auto dist(auto z0,  auto z1)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto dist[pedantic](auto z0,  auto z1) noexcept; //2
//!     constexpr auto dist[numeric](auto z0,  auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      1. Returns the distance between the two arguments computed as the absolute value of the arguments difference.
//!         The distance betwween an infinite an a nan value is nan
//!      2. if the pedantic option is used the distance betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic return zero if all corresponding parts satisfy `eve::is_equal[numeric]`.
//!
//!     Arguments can be a mix of floating or Cayley-Dickson values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dist.cpp}
//======================================================================================================================
  inline constexpr auto dist = eve::functor<dist_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto dist_(KYOSU_DELAY(), O const&, Z0 c0, Z1 c1) noexcept
  {
    auto d = kyosu::abs(c0-c1);

    if constexpr(O::contains(eve::pedantic) || O::contains(eve::numeric))
    {
      d = if_else(kyosu::is_infinite(c0) || kyosu::is_infinite(c1), eve::inf(as(d)), d);
      if constexpr(concepts::real<Z0> && concepts::real<Z1>)
      {
        if constexpr (O::contains(eve::pedantic)) return d;
        else return if_else(eve::is_equal[eve::numeric](c0, c1), zero, d);
      }
      else
      {
        if constexpr(O::contains(eve::numeric))
        {
          using r_t = decltype(c0-c1);
          auto eq = kumi::map([](auto a,  auto b) { return eve::is_equal[eve::numeric](a, b); }, r_t(c0), r_t(c1));
          return  if_else(kumi::all_of(eq), zero, d);
        }
        else
          return d;
      }
    }
    return d;
  }
}
