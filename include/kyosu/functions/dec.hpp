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
  struct dec_t : eve::elementwise_callable<dec_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z c) const noexcept
    {
      real(c) = eve::dec(real(c));
      return c;
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::dec(v); }

    KYOSU_CALLABLE_OBJECT(dec_t, dec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dec
//!   @brief decrements the argument by 1.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T dec(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T dec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to decrement.
//!
//!   **Return value**
//!
//!     Returns  its argument minus 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dec.cpp}
//======================================================================================================================
  inline constexpr auto dec = eve::functor<dec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
