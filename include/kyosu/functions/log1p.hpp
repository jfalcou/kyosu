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
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct log1p_t : eve::elementwise_callable<log1p_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(log1p_t, log1p_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log1p
//!   @brief Computes the natural logarithm of the argument plus 1.
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
//!      template<eve::floating_ordered_value T>     constexpr complex_t<T> log1p(T z) noexcept; //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr T log1p(T z) noexcept;            //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   1.  a real typed input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.\n
//!       For real and complex entries provision are made to get better precision near z = 0.
//!
//!   2.  returns [log](@ref kyosu::log)(1+z).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log1p.cpp}
//======================================================================================================================
  inline constexpr auto log1p = eve::functor<log1p_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log1p_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto m = kyosu::inc(z);
      auto arg = [](auto zz){ return eve::atan2[eve::pedantic](kyosu::imag(zz), kyosu::real(zz));};
      auto theta = eve::if_else((kyosu::is_real(m) && eve::is_nltz(kyosu::real(m))), eve::zero, arg(m)) ;
      auto rz =  kyosu::real(z);
      auto iz2 =  eve::sqr(kyosu::imag(z));
      auto r = eve::half(eve::as(theta))*eve::log1p(rz*(rz+2)+iz2);
      return complex(r, theta);
    }
    else
    {
      return cayley_extend(log1p, z);
    }
  }
}
