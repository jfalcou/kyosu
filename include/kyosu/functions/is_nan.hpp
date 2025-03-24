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
  struct is_nan_t : eve::elementwise_callable<is_nan_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return kumi::any_of(z, [](auto const& e) { return eve::is_nan(e); });
    }

    KYOSU_CALLABLE_OBJECT(is_nan_t, is_nan_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_nan
//!   @brief test the parameter for nan
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_nan(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is any component of the element is nan .
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_nan.cpp}
//======================================================================================================================
  inline constexpr auto is_nan = eve::functor<is_nan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
