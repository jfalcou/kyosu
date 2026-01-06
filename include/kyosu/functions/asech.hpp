//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/acosh.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct asech_t : eve::elementwise_callable<asech_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(asech_t, asech_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asech
//!   @brief Computes the inverse  hyperbolic secant of the argument.
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
//!     //  regular call
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> asech(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> asech[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real typed input z is treated as if `complex(z)` was entered unless the option real_only is used
//!     in which case the parameter must be a floating_value,  the real part of the result will the same as an `eve::asech`
//!     implying a Nan result if the result is not real.
//!   - Returns elementwise `acosh(rec(z))`.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Secant](https://mathworld.wolfram.com/InverseHyperbolicSecant.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF: Inverse hyperbolic function](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/asech.cpp}
//======================================================================================================================
  inline constexpr auto asech = eve::functor<asech_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asech_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    return  kyosu::acosh[o](kyosu::rec(z));
  }
}
