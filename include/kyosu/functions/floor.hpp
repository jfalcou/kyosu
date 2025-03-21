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
  struct floor_t : eve::elementwise_callable<floor_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(eve::floating_value<Z>)
        return eve::floor(z);
      else
        return Z{kumi::map([](auto const& e) { return eve::floor(e); }, z)};
    }

    KYOSU_CALLABLE_OBJECT(floor_t, floor_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var floor
//!   @brief Computes the floor value.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T floor(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which floor is computed.
//!
//!   **Return value**
//!
//!     Returns the floor of its argument. i.e. the value whose parts are the floor of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/floor.cpp}
//======================================================================================================================
  inline constexpr auto floor = eve::functor<floor_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
