//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/rec.hpp>


namespace kyosu
{
  template<typename Options>
  struct acoth_t : eve::elementwise_callable<acoth_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {      return kyosu::atanh(kyosu::rec(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

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
//!      template<eve::floating_ordered_value T>     constexpr auto acoth(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto acoth(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acoth(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real typed input z is treated as if `complex(z)` was entered.
//!
//!   2. Returns elementwise the complex principal value
//!      of the inverse hyperbolic cotangent of the input as the inverse hyperbolic tangent of the inverse of the input.
//!
//!   3. Returns \f$I_z \mathrm{acot}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
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

