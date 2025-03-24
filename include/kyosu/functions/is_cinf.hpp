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
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return eve::false_(eve::as(z));
      else
        return  kyosu::is_nan(z) && kyosu::is_infinite(z);
    }

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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_cinf(T z) noexcept;
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
