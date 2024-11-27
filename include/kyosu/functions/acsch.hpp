//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/asinh.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options>
  struct acsch_t : eve::elementwise_callable<acsch_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return asinh(rec(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(acsch_t, acsch_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acsch
//!   @brief Computes the inverse hyperbolic cosecant of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acsch(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acsch(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. A real type input z calls `eve::acsch(z)` and so returns the same type as input.
//!
//!   2. Returns elementwise `asinh(rec(z))`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acsch.cpp}
//======================================================================================================================
  inline constexpr auto acsch = eve::functor<acsch_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

