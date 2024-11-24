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
  struct acot_t : eve::elementwise_callable<acot_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {    return kyosu::atan(kyosu::rec(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::acot(v); }

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
//!      template<eve::floating_ordered_value T>     constexpr auto acot(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto acot(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acot(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. A real type input z calls eve::acot(z) and so returns the same type as the input.
//!
//!   2. Returns elementwise the complex principal value
//!      of the arc cotangent of the input as the arc tangent of the inverse of the input.
//!
//!   3. Returns \f$I_z \mathrm{acoth}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref pure)  part of \f$z\f$.
//!
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
