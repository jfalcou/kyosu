//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/constants/wrapped.hpp>


namespace kyosu
{
  template<typename Options>
  struct log_abs_t : eve::elementwise_callable<log_abs_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z const& z) const noexcept
    { return kyosu::half(kyosu::as<as_real_type_t<Z>>())*eve::log(kyosu::sqr_abs(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::log_abs(v); }

    KYOSU_CALLABLE_OBJECT(log_abs_t, log_abs_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log_abs
//!   @brief Computes the natural logarithm of the absolute value of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto log_abs(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto log_abs(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the `log(abs(z))`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log_abs.cpp}
//======================================================================================================================
  inline constexpr auto log_abs = eve::functor<log_abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
