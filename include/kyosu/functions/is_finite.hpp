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
  struct is_finite_t : eve::elementwise_callable<is_finite_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return kumi::all_of(z, [](auto const& e) { return eve::is_finite(e); });
    }

    KYOSU_CALLABLE_OBJECT(is_finite_t, is_finite_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_finite
//!   @brief test the parameter is finite.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_finite(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is all component of the element are finite .
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_finite.cpp}
//======================================================================================================================
  inline constexpr auto is_finite = eve::functor<is_finite_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
