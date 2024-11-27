//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/sqr.hpp>

namespace kyosu
{
  template<typename Options>
  struct expmx2_t : eve::elementwise_callable<expmx2_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {  return kyosu::exp(-sqr(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::expmx2(v); }

    KYOSU_CALLABLE_OBJECT(expmx2_t, expmx2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expmx2
//!   @brief Computes the exponential of the opposite of the squared argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T expmx2(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T expmx2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns `exp(-z*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/expmx2.cpp}
//======================================================================================================================
  inline constexpr auto expmx2 = eve::functor<expmx2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
