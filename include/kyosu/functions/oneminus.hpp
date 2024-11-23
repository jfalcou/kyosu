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
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/minus.hpp>
#include <iostream>

namespace kyosu
{
  template<typename Options>
  struct oneminus_t : eve::elementwise_callable<oneminus_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return inc(minus(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::oneminus(v); }

    KYOSU_CALLABLE_OBJECT(oneminus_t, oneminus_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var oneminus
//!   @brief Computes the value one minus the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T oneminus(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T oneminus(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: argument.
//!
//!   **Return value**
//!
//!     Returns one minus the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/oneminus.cpp}
//======================================================================================================================
  inline constexpr auto oneminus = eve::functor<oneminus_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
