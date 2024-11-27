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
  struct nearest_t : eve::elementwise_callable<nearest_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return Z{kumi::map([](auto const& e) { return eve::nearest(e); }, z)}; }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::nearest(v); }

    KYOSU_CALLABLE_OBJECT(nearest_t, nearest_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var nearest
//!   @brief Computes the nearest value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T nearest(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T nearest(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which nearest is computed.
//!
//!   **Return value**
//!
//!     Returns the nearest of its argument. i.e. the value with parts are the
//!     rounding to even of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/nearest.cpp}
//======================================================================================================================
  inline constexpr auto nearest = eve::functor<nearest_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
