//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/is_real.hpp>

namespace kyosu
{
  template<typename Options>
  struct is_flint_t : eve::elementwise_callable<is_flint_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return kyosu::is_real(z) && eve::is_flint(real(z));
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::is_flint(v); }

    KYOSU_CALLABLE_OBJECT(is_flint_t, is_flint_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_flint
//!   @brief test the parameter is a flint.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_flint(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_flint(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is the element is a floating integer .
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_flint.cpp}
//======================================================================================================================
  inline constexpr auto is_flint = eve::functor<is_flint_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
