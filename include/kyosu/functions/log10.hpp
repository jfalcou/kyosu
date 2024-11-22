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

namespace kyosu
{
  template<typename Options>
  struct log10_t : eve::elementwise_callable<log10_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    {  return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(log10_t, log10_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log10
//!   @brief Computes the base 10 logarithm of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto log10(T z) noexcept; //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto log10(T z) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   1.  a real typed input z is treated as if `complex(z)` was entered.
//!   2.  returns [log](@ref kyosu::log)(z)/log_10(as(z)).
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log10.cpp}
//======================================================================================================================
  inline constexpr auto log10 = eve::functor<log10_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto [rz, iz] = z;
      auto infty = eve::inf(eve::as(rz));
      auto arg = [](auto z){ return eve::atan2[eve::pedantic](kyosu::imag(z), kyosu::real(z));};
      auto argz = arg(z)*eve::invlog_10(eve::as(rz));
      auto absz = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz), infty, kyosu::abs(z));
      auto la = eve::log10(absz);
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), complex(la, eve::zero(eve::as(rz))), complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      return cayley_extend(log10, z);
    }
  }
}
