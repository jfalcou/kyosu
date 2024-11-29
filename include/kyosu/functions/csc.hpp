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
#include <kyosu/functions/sin.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options>
  struct csc_t : eve::elementwise_callable<csc_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return kyosu::rec(kyosu::sin(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::csc(v); }

    KYOSU_CALLABLE_OBJECT(csc_t, csc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var csc
//!   @brief Computes the cosecant of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T csc(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T csc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cosecant of the argument.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Cosecant](https://mathworld.wolfram.com/Cosecant.html)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/csc.cpp}
//======================================================================================================================
  inline constexpr auto csc = eve::functor<csc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
