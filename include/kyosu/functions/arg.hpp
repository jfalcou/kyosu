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
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z v) const noexcept
    {
      if constexpr(concepts::real<Z>)
      {
        return eve::if_else(eve::is_nan(v), eve::allbits, eve::if_else(eve::is_positive(v), eve::zero, eve::pi(eve::as(v))));
      }
      if constexpr(concepts::complex<Z>) return eve::atan2[ eve::pedantic](imag(v), real(v));
      else                               return eve::atan2[ eve::pedantic](eve::sign(imag(v))*abs(pure(v)), real(v));
    }

    KYOSU_CALLABLE_OBJECT(arg_t, arg_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var arg
//!   @brief  argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr as_real_type_t<Z> arg(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - For floating  value input, returns \f$0\f$ or \f$\pi\f$ according to the non negativity of `z` (arg of minus zero is \f$\pi\f$).
//!     - For complex  value input, returns elementwise the argument of the complex number i.e. `eve::atan2[pedantic](imag(z),real(z))`.
//!     - For general cayley_dickson,  returns \f$\mathrm{atan2}(\mathrm{sign}(z_1)|\underline{z}|, z_0)\f$ where \f$z_0\f$ is the real part of \f$z\f$,
//!       \f$z_1\f$ is the `ipart` of \f$z\f$ and \f$\underline{z}\f$ the `pure` part of \f$z\f$.
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
