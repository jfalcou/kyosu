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
  struct is_not_nan_t : eve::elementwise_callable<is_not_nan_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_not_nan(v); }

    KYOSU_CALLABLE_OBJECT(is_not_nan_t, is_not_nan_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_not_nan
//!   @brief test if the parameter is not a Nan.
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
//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_not_nan(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_not_nan(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise false is any component of the element is a Nan.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_not_nan.cpp}
//======================================================================================================================
  inline constexpr auto is_not_nan = eve::functor<is_not_nan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_not_nan_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    return kumi::all_of(c, [](auto const& e) { return eve::is_not_nan(e); });
  }
}
