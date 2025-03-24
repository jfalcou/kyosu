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
  struct is_denormal_t : eve::elementwise_callable<is_denormal_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& c) const noexcept
    {
      return kumi::any_of(c, [](auto const& e) { return eve::is_denormal(e); });
    }

    KYOSU_CALLABLE_OBJECT(is_denormal_t, is_denormal_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_denormal
//!   @brief test the parameter for denormality.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_denormal(T z) noexcept;
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
