//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_imag
//!   @brief test if the parameter real part is zero.
//!
//!   **Defined in Header**
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_imag(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_imag(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if the real part of the argument is zero.
//!     is_imag is an alias of is_pure.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_imag.cpp}
//! @}
//======================================================================================================================
}
