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
  struct is_nez_t : eve::elementwise_callable<is_nez_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_nez(v); }

    KYOSU_CALLABLE_OBJECT(is_nez_t, is_nez_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_nez
//!   @brief test the parameter for non-equality to zero.
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
//!   namespace kyosu//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_nez(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_nez(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is any component of the element is not zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_nez.cpp}
//======================================================================================================================
  inline constexpr auto is_nez = eve::functor<is_nez_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_nez_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    return kumi::any_of(c, [](auto const& e) { return eve::is_nez(e); });
  }
}
