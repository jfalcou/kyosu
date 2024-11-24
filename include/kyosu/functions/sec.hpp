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
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/cos.hpp>

namespace kyosu
{
  template<typename Options>
  struct sec_t : eve::elementwise_callable<sec_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return kyosu::rec(kyosu::cos(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sec(v); }

    KYOSU_CALLABLE_OBJECT(sec_t, sec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sec
//!   @brief Computes the secant of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto sec(T z) noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!    Returns the secant of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sec.cpp}
//======================================================================================================================
  inline constexpr auto sec = eve::functor<sec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
