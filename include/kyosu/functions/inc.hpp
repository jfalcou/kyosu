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
  struct inc_t : eve::elementwise_callable<inc_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::inc(v); }

    KYOSU_CALLABLE_OBJECT(inc_t, inc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var inc
//!   @brief Increments the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T inc(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T inc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to increment.
//!
//!   **Return value**
//!
//!     Returns  its argument plus 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/inc.cpp}
//======================================================================================================================
  inline constexpr auto inc = eve::functor<inc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto inc_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    real(c) = eve::inc(real(c));
    return c;
  }
}
