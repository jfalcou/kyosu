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
  struct is_eqz_t : eve::elementwise_callable<is_eqz_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_eqz(v); }

    KYOSU_CALLABLE_OBJECT(is_eqz_t, is_eqz_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_eqz
//!   @brief test the parameter for equality to zero.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_eqz(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_eqz(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the value of z == 0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_eqz.cpp}
//======================================================================================================================
  inline constexpr auto is_eqz = eve::functor<is_eqz_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_eqz_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    return z == eve::zero(as(z));
  }
}
