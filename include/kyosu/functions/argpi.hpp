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
  struct argpi_t : eve::elementwise_callable<argpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z v) const noexcept
    {
      return KYOSU_CALL(v);
    }

    KYOSU_CALLABLE_OBJECT(argpi_t, argpi_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var argpi
//!   @brief  argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<Z> argpi(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - For floating  value input, returns \f$0\f$ or \f$1\f$ according to the non negativity of `z` (argpi of minus zero is 1).
//!     - For complex  value input, returns elementwise the argument of the complex number in \f$\pi\f$ multiples i.e. `eve::atan2pi[pedantic](imag(z),real(z))`.
//!     - For general cayley_dickson,  returns \f$\mathrm{atan2pi}(\mathrm{sign}(z_1)|\underline{z}|, z_0)\f$ where \f$z_0\f$ is the real part of \f$z\f$,
//!       \f$z_1\f$ is the `ipart` of \f$z\f$ and \f$\underline{z}\f$ the `pure` part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/argpi.cpp}
//======================================================================================================================
  inline constexpr auto argpi = eve::functor<argpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto argpi_(KYOSU_DELAY(), O const&, Z v) noexcept
  {
    if constexpr(concepts::real<Z>)
    {
      return eve::if_else(eve::is_nan(v), eve::allbits, eve::if_else(eve::is_positive(v), eve::zero, eve::one(eve::as(v))));
    }
    if constexpr(concepts::complex<Z>) return eve::atan2pi[ eve::pedantic](imag(v), real(v));
    else                               return eve::atan2pi[ eve::pedantic](eve::sign(imag(v))*abs(pure(v)), real(v));
  }
}
