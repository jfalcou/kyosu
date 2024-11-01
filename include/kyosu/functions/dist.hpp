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
  struct dist_t : eve::elementwise_callable<dist_t, Options>
  {
    template<eve::value Z0, eve::value Z1>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept -> decltype(kyosu::abs(c0-c1))
    {
      return kyosu::abs(c0-c1);
    }

    KYOSU_CALLABLE_OBJECT(dist_t, dist_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dist
//!   @brief Computes the distance between the two parameters.
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
//!     constexpr auto dist(auto z0,  auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the distance between the two arguments computed as the distolute value of the arguments difference.
//!     Arguments can be a mix of floating or Cayley-Dicson values.
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
