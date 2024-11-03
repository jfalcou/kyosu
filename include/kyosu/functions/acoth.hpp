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
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(acoth_t, acoth_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acoth
//!   @brief Computes the arg hyperbolic cotangent of the argument.
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
//!   1. A real type input z calls eve::acoth(z); and so returns the same type as the input.
//!
//!   2. Returns elementwise the complex principal value
//!      of the ar hyperbolic cotangent of the input as the arc tangent of the inverse of the input.
//!
//!   3. Returns \f$I_z \mathrm{acot}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acoth.cpp}
//======================================================================================================================
  inline constexpr auto acoth = eve::functor<acoth_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acoth_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
     return kyosu::atanh(kyosu::rec(z));
  }
}
