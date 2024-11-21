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
#include <kyosu/functions/sqr.hpp>

namespace kyosu
{
  template<typename Options>
  struct expx2_t : eve::elementwise_callable<expx2_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::expx2(v); }

    KYOSU_CALLABLE_OBJECT(expx2_t, expx2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expx2
//!   @brief Computes the exponential of the squared argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T expx2(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T expx2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns `exp(z*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/expx2.cpp}
//======================================================================================================================
  inline constexpr auto expx2 = eve::functor<expx2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto expx2_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    return exp(sqr(z));
  }
}
