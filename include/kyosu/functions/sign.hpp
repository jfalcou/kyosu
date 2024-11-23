//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/is_nez.hpp>
#include <kyosu/functions/abs.hpp>

namespace kyosu
{
  template<typename Options>
  struct sign_t : eve::elementwise_callable<sign_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& c) const noexcept
    {     return kyosu::if_else(kyosu::is_nez(c), c/abs(c), eve::zero); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sign(v); }

    KYOSU_CALLABLE_OBJECT(sign_t, sign_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sign
//!   @brief Computes tne normalized value z/abs(z) if z is not zero else 0.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T sign(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T sign(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the "sign" of the argument i.e. its normalized value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sign.cpp}
//======================================================================================================================
  inline constexpr auto sign = eve::functor<sign_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
