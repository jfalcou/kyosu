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
  struct is_pure_t : eve::elementwise_callable<is_pure_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return eve::is_eqz(real(z));
    }

     KYOSU_CALLABLE_OBJECT(is_pure_t, is_pure_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_pure
//!   @brief test if the parameter is pure.
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
//!      template<kyosu::concepts::cayley_dickson_like T>    constexpr auto is_pure(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if the [real](@ref kyosu::real) part of the argument is zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_pure.cpp}
//======================================================================================================================
  inline constexpr auto is_pure = eve::functor<is_pure_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
