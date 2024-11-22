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
    KYOSU_FORCEINLINE constexpr as_real_type_t<Z> operator()(Z v) const noexcept
    {
      if      constexpr(concepts::complex<Z>)        return eve::atan2[ eve::pedantic](imag(v), real(v));
      else if constexpr(concepts::cayley_dickson<Z>) return eve::atan2[ eve::pedantic](eve::sign(imag(v))*abs(pure(v)), real(v));
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept {
      return eve::if_else(eve::is_positive(v), eve::zero, eve::pi(eve::as(v)));
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
//!     1. Returns \f$0\f$ or \f$\pi\f$ according to the non negativity of `z` (arg of minus zero is \f$\pi\f$).
//!     2. Returns elementwise the argument of the complex number i.e. `eve::atan2[pedantic](imag(z),real(z))`.
//!     3. Returns \f$\mathrm{atan2}(\mathrm{sign}(z_1)|\underline{z}|, z_0)\f$ where \f$z_0\f$ is the real part of \f$z\f$,  \f$z_1\f$ is the `ipart` of \f$z\f$ and
//!         \f$\underline{z}\f$ the `pure` part of \f$z\f$.
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
    if      constexpr(concepts::complex<Z>)        return  eve::atan2[ eve::pedantic]( imag(v), real(v));
    else if constexpr(concepts::cayley_dickson<Z>) return  eve::atan2[ eve::pedantic](  eve::sign(imag(v))*abs(pure(v)), real(v));
    else                                           return  eve::if_else( eve::is_positive(v), eve::zero, eve::pi(eve::as(v)));
  }
}
