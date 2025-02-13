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
  struct is_cinf_t : eve::elementwise_callable<is_cinf_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
//      return  eve::is_nan(kyosu::real(z)) && eve::is_pinf(kyosu::imag(z));
      return  kyosu::is_nan(z) && kyosu::is_infinite(z);
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::false_(eve::as(v)); }

    KYOSU_CALLABLE_OBJECT(is_cinf_t, is_cinf_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_cinf
//!   @brief test if the parameter is a `cinf`.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_cinf(T z) noexcept; /1
//!      template<eve::floating_ordered_value T>     constexpr auto is_cinf(T z) noexcept; /2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if it has both an infinite AND a NaN part.
//!     This is meant to represent a quantity with infinite magnitude, but undetermined complex phase.
//!     This is always false for real entries.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: complex infinity](https://reference.wolfram.com/language/ref/ComplexInfinity.html)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_cinf.cpp}
//======================================================================================================================
  inline constexpr auto is_cinf = eve::functor<is_cinf_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
