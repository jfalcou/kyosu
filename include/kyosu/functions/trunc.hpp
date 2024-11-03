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
  struct trunc_t : eve::elementwise_callable<trunc_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::trunc(v); }

    KYOSU_CALLABLE_OBJECT(trunc_t, trunc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var trunc
//!   @brief Computes the trunc value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T trunc(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T trunc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which trunc is computed.
//!
//!   **Return value**
//!
//!     Returns the truncation of its argument. i.e. the value with parts are the
//!     rounding toward zero of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/trunc.cpp}
//======================================================================================================================
  inline constexpr auto trunc = eve::functor<trunc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto trunc_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    return Z{kumi::map([](auto const& e) { return eve::trunc(e); }, c)};
  }
}
