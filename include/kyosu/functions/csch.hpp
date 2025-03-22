//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sinh.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options>
  struct csch_t : eve::elementwise_callable<csch_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::reale<Z>)
        return eve::csch(z);
      if constexpr(concepts::complex<Z> )
        return kyosu::rec(kyosu::sinh(z));
      else
        return _::cayley_extend(*this, z);
    }

    KYOSU_CALLABLE_OBJECT(csch_t, csch_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var csch
//!   @brief Computes the hyperbolic cosecant of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T csch(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic cosecant of the argument.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Hyperbolic Cosecant](https://mathworld.wolfram.com/HyperbolicCosecant.html)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/csch.cpp}
//======================================================================================================================
  inline constexpr auto csch = eve::functor<csch_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
