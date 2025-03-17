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
  struct abs_t : eve::elementwise_callable<abs_t, Options, eve::raw_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z v) const noexcept
    {
      if constexpr(concepts::real <Z>)
        return eve::abs(v);
      else if constexpr(Options::contains(eve::raw))
        return eve::hypot(v);
      else
        return eve::hypot[eve::pedantic](v);
    }

    KYOSU_CALLABLE_OBJECT(abs_t, abs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var abs
//!   @brief Computes the absolute value of the parameter.
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
//!      //regular calls
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<T> abs(T z) noexcept;       // 1
//!
//!      // Semantic modifyiers
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<T> abs[raw](T z) noexcept;  // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    1. The  modulus of its parameter (always a floating ordered value).
//!       The modulus is the square root of the sum of the squares of the absolute value of each component.
//!    2. With the raw option no provision is made to enhance accuracy and avoid overflows
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex abs](https://en.cppreference.com/w/cpp/numeric/complex/abs)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/abs.cpp}
//======================================================================================================================
  inline constexpr auto abs = eve::functor<abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
