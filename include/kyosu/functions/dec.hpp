//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct dec_t : eve::elementwise_callable<dec_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

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

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto dec_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    real(c) = eve::dec(real(c));
    return c;
  }
}
