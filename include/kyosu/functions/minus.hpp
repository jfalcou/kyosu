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
  struct minus_t : eve::elementwise_callable<minus_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {     return -z; }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::minus(v); }

    KYOSU_CALLABLE_OBJECT(minus_t, minus_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var minus
//!   @brief Computes the opposite value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T minus(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T minus(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the opposite of its argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/minus.cpp}
//======================================================================================================================
  inline constexpr auto minus = eve::functor<minus_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
