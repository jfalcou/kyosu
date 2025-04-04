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
  struct is_infinite_t : eve::elementwise_callable<is_infinite_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }
    
    KYOSU_CALLABLE_OBJECT(is_infinite_t, is_infinite_);
  };
  
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_infinite
//!   @brief test if the parameter is infinite.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_infinite(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is any component of the element is infinite .
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_infinite.cpp}
//======================================================================================================================
  inline constexpr auto is_infinite = eve::functor<is_infinite_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_infinite_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    return kumi::any_of(z, [](auto e) { return eve::is_infinite(e); });
  }
}
