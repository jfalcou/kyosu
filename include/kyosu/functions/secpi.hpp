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
#include <kyosu/functions/cospi.hpp>

namespace kyosu
{
  template<typename Options>
  struct secpi_t : eve::elementwise_callable<secpi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return kyosu::rec(kyosu::cospi(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::secpi(v); }

    KYOSU_CALLABLE_OBJECT(secpi_t, secpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var secpi
//!   @brief Computes the secant of the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto secpi(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto secpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the secant of the argument in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/secpi.cpp}
//======================================================================================================================
  inline constexpr auto secpi = eve::functor<secpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
