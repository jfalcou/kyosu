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
  struct acot_t : eve::elementwise_callable<acot_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(acot_t, acot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acot
//!   @brief Computes the arc cotangent of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T acot(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!    - A real typed input z calls eve::acot(z) and so returns the same type as the input.
//!    - For complex input, returns elementwise the complex principal value
//!        of the arc cotangent of the input as the arc tangent of the inverse of the input.
//!    - For other general cayley_dickson input, returns \f$I_z \mathrm{acoth}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref pure)  part of \f$z\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cotangent](https://mathworld.wolfram.com/InverseCotangent.html)
//!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/acot.cpp}
//======================================================================================================================
  inline constexpr auto acot = eve::functor<acot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acot_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::acot(z);
    else
      return kyosu::atan(kyosu::rec(z));
  }
}
