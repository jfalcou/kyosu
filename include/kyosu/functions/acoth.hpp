//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/rec.hpp>


namespace kyosu
{
  template<typename Options>
  struct acoth_t : eve::elementwise_callable<acoth_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>) return (*this)(complex(z));
      else                            return kyosu::atanh(kyosu::rec(z));
    }

    KYOSU_CALLABLE_OBJECT(acoth_t, acoth_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acoth
//!   @brief Computes the inverse  hyperbolic cotangent of the argument.
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
//!     constexpr complexify_t<Z> acoth(concepts::cayley_dickson_like auto z) noexcept;
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
//!   - For complex input, returns elementwise the complex principal value
//!      of the inverse hyperbolic cotangent of the input as the inverse hyperbolic tangent of the inverse of the input.
//!
//!   - For general cayley_dickson input, returns \f$I_z \mathrm{acot}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Cotangent](https://mathworld.wolfram.com/InverseHyperbolicCotangent.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF: Inverse hyperbolic functions](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/acoth.cpp}
//======================================================================================================================
  inline constexpr auto acoth = eve::functor<acoth_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
