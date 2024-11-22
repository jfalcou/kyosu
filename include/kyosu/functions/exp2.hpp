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
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct exp2_t : eve::elementwise_callable<exp2_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {     return kyosu::exp(z*kyosu::log_2(eve::as_element<Z>())); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::exp2(v); }

    KYOSU_CALLABLE_OBJECT(exp2_t, exp2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp2
//!   @brief Computes the base 2 exponential of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T exp2(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T exp2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns 2 to the argument. The call is semantically equivalent to \f$e^{\log(2)z}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp2.cpp}
//======================================================================================================================
  inline constexpr auto exp2 = eve::functor<exp2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
