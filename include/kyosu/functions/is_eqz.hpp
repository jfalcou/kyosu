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
  struct is_eqz_t : eve::elementwise_callable<is_eqz_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return z == eve::zero(as(z));
    }

    KYOSU_CALLABLE_OBJECT(is_eqz_t, is_eqz_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_eqz
//!   @brief test the parameter for equality to zero.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_eqz(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the value of z == 0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_eqz.cpp}
//======================================================================================================================
  inline constexpr auto is_eqz = eve::functor<is_eqz_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
