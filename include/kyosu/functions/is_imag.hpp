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
  struct is_imag_t : eve::elementwise_callable<is_imag_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
       KYOSU_CALL(z);
  }

    KYOSU_CALLABLE_OBJECT(is_imag_t, is_imag_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_imag
//!   @brief test if the parameter real part is zero.
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
//!   {
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_imag(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if the real part of the argument is zero.
//!     is_imag is an alias of is_pure.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_imag.cpp}
//======================================================================================================================
  inline constexpr auto is_imag = eve::functor<is_imag_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
   template<typename Z, eve::callable_options O>
   KYOSU_FORCEINLINE constexpr auto is_imag_(KYOSU_DELAY(), O const&, Z z) noexcept
   {
      return eve::is_eqz(real(z));
  }
}
