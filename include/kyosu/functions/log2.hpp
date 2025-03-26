//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/if_else.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct log2_t : eve::elementwise_callable<log2_t, Options>
  {
   template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>) return (*this)(complex(z));
      else                            return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(log2_t, log2_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log2
//!   @brief Computes the base 2 logarithm of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T log2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - real typed input z is treated as if `complex(z)` was entered.
//!     - returns [log](@ref kyosu::log)(z)/log_2(as(z)).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Binary Logarithm](https://en.wikipedia.org/wiki/Binary_logarithm)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/log2.cpp}
//======================================================================================================================
  inline constexpr auto log2 = eve::functor<log2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z log2_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto [rz, iz] = z;
      auto infty = eve::inf(eve::as(rz));
      auto arg = [](auto z){ return eve::atan2[eve::pedantic](kyosu::imag(z), kyosu::real(z));};
      auto argz = arg(z)*eve::invlog_2(eve::as(rz));
      auto absz = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz), infty, kyosu::abs(z));
      auto la = eve::log2(absz);
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), complex(la), complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      return _::cayley_extend(kyosu::log2, z);
    }
  }
}
