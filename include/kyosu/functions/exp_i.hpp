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
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/muli.hpp>

namespace kyosu
{
  template<typename Options>
  struct exp_i_t : eve::elementwise_callable<exp_i_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return kyosu::exp(muli(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(exp_i_t, exp_i_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp_i
//!   @brief Computes the exponential of i times the argument
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T exp_i(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T exp_i(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns `exp(i*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp_i.cpp}
//======================================================================================================================
  inline constexpr auto exp_i = eve::functor<exp_i_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
