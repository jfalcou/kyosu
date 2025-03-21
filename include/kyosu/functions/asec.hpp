//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/acos.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct asec_t : eve::elementwise_callable<asec_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return  kyosu::acos(kyosu::rec(z));
    }

    KYOSU_CALLABLE_OBJECT(asec_t, asec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asec
//!   @brief Computes the arcsecant of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto asec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real typed input z is treated as if `complex(z)` was entered.
//!   - For complex input, returns elementwise `acos(rec(z))`.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Secant](https://mathworld.wolfram.com/InverseSecant.html)
//!   *  [Wikipedia: Inverse trigonometric functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/asec.cpp}
//======================================================================================================================
  inline constexpr auto asec = eve::functor<asec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
