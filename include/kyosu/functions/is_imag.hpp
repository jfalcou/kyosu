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
  struct is_imag_t : eve::elementwise_callable<is_imag_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return eve::is_eqz(real(z));
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_eqz(v); }

    KYOSU_CALLABLE_OBJECT(is_imag_t, is_imag_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_imag
//!   @brief test if the parameter real part is zero.
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
//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_imag(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_imag(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if the real part of the argument is zero.
//!     is_imag is an alias of is_pure.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_imag.cpp}
//======================================================================================================================
  inline constexpr auto is_imag = eve::functor<is_imag_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
