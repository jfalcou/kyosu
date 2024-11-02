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
  struct is_denormal_t : eve::elementwise_callable<is_denormal_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_denormal(v); }

    KYOSU_CALLABLE_OBJECT(is_denormal_t, is_denormal_);
  };

//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_denormal(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_denormal(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is at least one component of the element is denormal.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_denormal.cpp}
//======================================================================================================================
  inline constexpr auto is_denormal = eve::functor<is_denormal_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_denormal_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
     return kumi::any_of(c, [](auto const& e) { return eve::is_denormal(e); });
  }
}
