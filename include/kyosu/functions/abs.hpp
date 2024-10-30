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
  struct abs_t : eve::elementwise_callable<abs_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept { return KYOSU_CALL(v); }

    KYOSU_CALLABLE_OBJECT(abs_t, abs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var abs
//!   @brief Computes the absolute value of the parameter.
//!
//!   **Defined in Header**
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr as_real_type_t<T> abs(T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T                 abs(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!   The modulus of its argument which always is a floating ordered value.
//!   The modulus is the square root of the sum of the square of the absolute value of each component.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/abs.cpp}
//======================================================================================================================

  inline constexpr auto abs = eve::functor<abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto abs_(KYOSU_DELAY(), O const&, Z const& v) noexcept
  {
    if constexpr(concepts::cayley_dickson<Z>) return eve::hypot[eve::pedantic](v);
    else                                      return eve::abs(v);
  }
}
