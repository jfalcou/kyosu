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
  struct is_nez_t : eve::elementwise_callable<is_nez_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
       KYOSU_CALL(z);
  }

    KYOSU_CALLABLE_OBJECT(is_nez_t, is_nez_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_nez
//!   @brief test the parameter for non-equality to zero.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_nez(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is any component of the element is not zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_nez.cpp}
//======================================================================================================================
  inline constexpr auto is_nez = eve::functor<is_nez_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
   template<typename Z, eve::callable_options O>
   KYOSU_FORCEINLINE constexpr auto is_nez_(KYOSU_DELAY(), O const&, Z z) noexcept
   {
      return kumi::any_of(z, [](auto const& e) { return eve::is_nez(e); });
  }
}
