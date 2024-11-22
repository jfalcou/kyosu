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
  struct is_not_finite_t : eve::elementwise_callable<is_not_finite_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return kumi::any_of(z, [](auto const& e) { return eve::is_not_finite(e); });
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_not_finite(v); }

    KYOSU_CALLABLE_OBJECT(is_not_finite_t, is_not_finite_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_not_finite
//!   @brief test if the parameter is not finite.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_not_finite(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_not_finite(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is any component of the element is not finite .
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_not_finite.cpp}
//======================================================================================================================
  inline constexpr auto is_not_finite = eve::functor<is_not_finite_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
