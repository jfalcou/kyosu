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
  struct frac_t : eve::elementwise_callable<frac_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {   return Z{kumi::map([](auto const& e) { return eve::frac(e); }, z)}; }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::frac(v); }

    KYOSU_CALLABLE_OBJECT(frac_t, frac_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var frac
//!   @brief Computes the frac value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T frac(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T frac(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the fractionnal part of its argument. i.e. the value whose parts are the fractionnal
//!     parts of the original ones.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/frac.cpp}
//======================================================================================================================
  inline constexpr auto frac = eve::functor<frac_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
