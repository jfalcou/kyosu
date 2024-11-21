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

namespace kyosu
{
  template<typename Options>
  struct ceil_t : eve::elementwise_callable<ceil_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::ceil(v); }

    KYOSU_CALLABLE_OBJECT(ceil_t, ceil_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var ceil
//!   @brief Computes the ceil value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T ceil(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T ceil(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value for which ceil is computed.
//!
//!   **Return value**
//!
//!     Returns the ceil of its argument. i.e. the value with parts are the ceil of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/ceil.cpp}
//======================================================================================================================
  inline constexpr auto ceil = eve::functor<ceil_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto ceil_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    return Z{kumi::map([](auto const& e) { return eve::ceil(e); }, c)};
  }
}
