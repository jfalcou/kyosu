//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct ceil_t : eve::elementwise_callable<ceil_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

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
//!     template<kyosu::concepts::cayley_dickson_like T> constexpr T ceil(T z) noexcept;
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
  KYOSU_FORCEINLINE constexpr auto ceil_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::real<Z>)
      return eve::ceil(z);
    else
      return Z{kumi::map([](auto const& e) { return eve::ceil(e); }, z)};
  }
}
