//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct arg_t : eve::elementwise_callable<arg_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept { return KYOSU_CALL(v); }

    KYOSU_CALLABLE_OBJECT(arg_t, arg_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var arg
//!   @brief  argument.
//!
//!   **Defined in Header**
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
//!      template<eve::floating_ordered_value T>     constexpr auto arg(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr auto arg(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto arg(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns 0 or pi according to the non negativity of z.
//!     2. Returns elementwise the argument of the complex number i.e. eve::atan2([kyosu::imag](@ref kyosu::imag )(z), [kyosu::real](@ref kyosu::real )(z)).
//!     3. Returns \f$\mathrm{atan2}(\mathrm{sign}(z_1)|\underline{z}|, z_0)\f$ where \f$z_0\f$ is the real part of \f$z\f$,  \f$z_1\f$ is the ipart of \f$z\f$ and
//!         \f$\underline{z}\f$ the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/arg.cpp}
//======================================================================================================================
  inline constexpr auto arg = eve::functor<arg_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto arg_(KYOSU_DELAY(), O const&, Z const& v) noexcept
  {
    using eve::atan2;
    using eve::if_else;
    using eve::is_positive;
    using eve::pedantic;
    using eve::sign;

    if      constexpr(concepts::complex<Z>)         return atan2[pedantic]( imag(v), real(v));
    else if constexpr(concepts::cayley_dickson<Z>)  return atan2[pedantic]( sign(imag(v)) * abs(pure(v)), real(v));
    else                                            return if_else(is_positive(v), eve::zero, eve::pi(eve::as(v)));
  }
}