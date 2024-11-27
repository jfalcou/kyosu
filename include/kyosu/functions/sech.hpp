//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/cosh.hpp>

namespace kyosu
{
  template<typename Options>
  struct sech_t : eve::elementwise_callable<sech_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {  return kyosu::rec(kyosu::cosh(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sech(v); }

    KYOSU_CALLABLE_OBJECT(sech_t, sech_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sech
//!   @brief Computes the hyperbolic secant of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sech(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sech(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic secant of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sech.cpp}
//======================================================================================================================
  inline constexpr auto sech = eve::functor<sech_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
