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
  struct manhattan_t : eve::elementwise_callable<manhattan_t, Options>
  {
    template<eve::value Z0, eve::value ...Zs>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 z0, Zs... zs) const noexcept //-> decltype(kyosu::abs(z0 + ... + zs))
    {
       return eve::manhattan(kumi::flatten(kumi::cat(z0, zs...)));
    }

    KYOSU_CALLABLE_OBJECT(manhattan_t, manhattan_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var manhattan
//!   @brief Computes the relative distance between the two parameters.
//!
//!   **Defined in Header**
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
//!     constexpr auto manhattan(auto z0, auto z1) noexcept;
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
//!  @godbolt{doc/manhattan.cpp}
//======================================================================================================================
  inline constexpr auto manhattan = eve::functor<manhattan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
