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
  struct log10_t : eve::elementwise_callable<log10_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like  Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<Z, K> operator()(Z const& z, K const & k) const noexcept
    {
      return KYOSU_CALL(z, k);
    }

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
//!      //  regular call
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log10(T z) noexcept;             \\1
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log10(T z eve::value n) noexcept;\\2
//!
//!      // semantic modifyers
//!      template<concepts::real T> constexpr complexify_t<T> log10[real_only](T z) noexcept;                        \\3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   1.  a real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
//!       in which case the parameter must be a floating_value,  the  result will the same as to an `eve::log10` call
//!       implying a Nan result if the  input is not greater than zero.
//!   2.  returns [log](@ref kyosu::log)(z)/log_10(as(z)).
//!   3.  with two parameters return the nth branch of the function.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Common Logarithm](https://mathworld.wolfram.com/CommonLogarithm.html)
//!   *  [Wikipedia: Logarithm](https://en.wikipedia.org/wiki/Logarithm)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/log10.cpp}
//======================================================================================================================
  inline constexpr auto log10 = eve::functor<log10_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::real Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), O const&o, Z z) noexcept
  {
    if constexpr(O::contains(real_only))
      return eve::log10(z);
    else
      return complex(eve::log_abs(z)*eve::invlog_10(eve::as(z)), eve::arg(z)*eve::invlog_10(eve::as(z)));
  };

  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), O const&o, Z z) noexcept
  requires(!concepts::real<Z>)
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto [rho, theta] = to_polar(z);
      return Z(eve::log10(rho), theta*eve::invlog_10(eve::as(theta)));
    }
    else
      return _::cayley_extend(kyosu::log10, z);
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log10_(KYOSU_DELAY(), O const&o, Z z, K k) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto [r, i] = log10(z);
      auto kk = eve::convert(k, as<e_t>());
      return Z(r, (i+kk*two_pi(as(kk))*eve::invlog_10(eve::as(kk))));
    }
    else
      return _::cayley_extend(kyosu::log10, z, k);
  }
}
