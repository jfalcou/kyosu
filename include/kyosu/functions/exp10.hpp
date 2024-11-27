//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct exp10_t : eve::elementwise_callable<exp10_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {   return kyosu::exp(z*kyosu::log_10(eve::as_element<Z>())); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::exp10(v); }

    KYOSU_CALLABLE_OBJECT(exp10_t, exp10_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp10
//!   @brief Computes the base 10 exponential of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T exp10(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T exp10(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns 10 to the argument. The call is semantically equivalent to \f$e^{\log(10)z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp10.cpp}
//======================================================================================================================
  inline constexpr auto exp10 = eve::functor<exp10_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
