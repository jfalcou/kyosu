//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct log1p_t : eve::elementwise_callable<log1p_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return  KYOSU_CALL(z);
    }

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
//!      template<kyosu::concepts::cayley_dickson_likeT> constexpr complexify_t<T> log1p(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - A real typed input z is treated as if `complex(z)` was entered.\n
//!     - For real and complex entries provisions are made to get better precision near z = 0.
//!     - Returns [log](@ref kyosu::log)(1+z).
//!
//!  @groupheader{Example}
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
  constexpr auto log1p_(KYOSU_DELAY(), O const&, Z z) noexcept
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
      return _::cayley_extend(kyosu::log1p, z);
    }
  }
}
