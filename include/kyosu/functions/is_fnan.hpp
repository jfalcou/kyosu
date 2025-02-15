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
  struct is_fnan_t : eve::elementwise_callable<is_fnan_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return kumi::all_of(z, [](auto const& e) { return eve::is_nan(e); });
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_nan(v); }

    KYOSU_CALLABLE_OBJECT(is_fnan_t, is_fnan_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_fnan
//!   @brief test the parameter for fnan
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_fnan(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_fnan(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is all components of the element are NaNs.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_fnan.cpp}
//======================================================================================================================
  inline constexpr auto is_fnan = eve::functor<is_fnan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
