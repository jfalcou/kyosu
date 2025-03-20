//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/cosh.hpp>
#include <kyosu/functions/muli.hpp>
namespace kyosu
{
  template<typename Options>
  struct cos_t : eve::elementwise_callable<cos_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z> )
        return eve::cos(z);
      else
        return cosh(muli(z));
    }

    KYOSU_CALLABLE_OBJECT(cos_t, cos_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cos
//!   @brief Computes the cosine of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T cos(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - A floating value typed input z calls eve::asinh(z) and so returns the same type as input.
//!     - returns the cosine of the argument.
//!     - For general cayley_dickson, eturns \f$\cosh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\cos(z_0)\f$, where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex cos](https://en.cppreference.com/w/cpp/numeric/complex/cos)
//!   *  [Wolfram MathWorld: Cosine](https://mathworld.wolfram.com/Cosine.html)
//!   *  [Wikipedia: cosinus](https://fr.wikipedia.org/wiki/cosinus)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/cos.cpp}
//======================================================================================================================
  inline constexpr auto cos = eve::functor<cos_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
