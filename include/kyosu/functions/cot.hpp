//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/tan.hpp>

namespace kyosu
{
  template<typename Options>
  struct cot_t : eve::elementwise_callable<cot_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(cot_t, cot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cot
//!   @brief Computes the cotangent of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T cot(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cotangent of the argument.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Cotangent](https://mathworld.wolfram.com/Cotangent.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/cot.cpp}
//======================================================================================================================
  inline constexpr auto cot = eve::functor<cot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cot_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::cot(z);
    else if constexpr(concepts::complex<Z> )
      return kyosu::rec(kyosu::tan(z));
    else
      return _::cayley_extend(kyosu::cot, z);
  }
}
