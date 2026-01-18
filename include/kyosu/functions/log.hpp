//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_polar.hpp>
#include <kyosu/functions/muli.hpp>
#include <iostream>

namespace kyosu
{
  template<typename Options>
  struct log_t : eve::strict_elementwise_callable<log_t, Options, real_only_option>
  {
    template<concepts::real Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    requires(!concepts::real<Z>)
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<Z, K> operator()(Z const& z, K const & k) const noexcept
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(log_t, log_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log
//!   @brief Computes the natural logarithm of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log(T z) noexcept;
//!
//!      // semantic modifyers
//!      template<concepts::real T> constexpr complexify_t<T> log[real_only](T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!    - A real typed input z is treated as if `complex(z)` was entered, unless the option `real_only` is used
//!       in which case the  result will the same as an `eve::log` call
//!       implying a Nan result if the input is not greater than zero.
//!    - For complex entry returns elementwise the natural logarithm of the input
//!      in the range of a strip in the interval \f$i\times[-\pi, \pi]\f$ along the imaginary axis
//!      and mathematically unbounded along the real axis. .
//!
//!      * The function is continuous onto the branch cut  along the negative real axis,
//!        taking into account the sign of imaginary part
//!      * for every z: `log(conj(z)) == conj(log(z))`
//!      * If z is \f$-0\f$, the result is \f$-\infty+i \pi \f$
//!      * If z is \f$+0\f$, the result is \f$-\infty\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$\infty+i \pi/2\f$
//!      * If z is \f$x+i \textrm{NaN}\f$ (for any finite x), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite positive y), the result is \f$\infty+i \pi \f$
//!      * If z is \f$+\infty+i y\f$ (for any finite positive y), the result is \f$\infty\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$\infty+i 3\pi/4\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$\infty+i \pi/4\f$
//!      * If z is \f$\pm\infty+i \textrm{NaN}\f$, the result is \f$\infty+i \textrm{NaN}\f$
//!      * If z is \f$\textrm{NaN}+i y\f$ (for any finite y), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
//!      * If z is \f$\textrm{NaN}+i \infty\f$, the result is \f$\infty+i \textrm{NaN}\f$
//!      * If z is \f$\textrm{NaN}+i \textrm{NaN}\f$, the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
//!    - For general cayley_dickson entry`log(z)` is semantically equivalent to `log(abs(z)) + sign(pure(z)) * arg(z)`
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Logarithm](https://mathworld.wolfram.com/Logarithm.html)
//!   *  [DLMF: Logarithm](https://dlmf.nist.gov/4.2)
//!   *  [Wikipedia: Logarithm](https://en.wikipedia.org/wiki/Logarithm)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/log.cpp}
//======================================================================================================================
  inline constexpr auto log = eve::functor<log_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::real Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_(KYOSU_DELAY(), O const&o, Z z) noexcept
  {
    if constexpr(O::contains(real_only))
      return eve::log(z);
    else
      return complex(eve::log_abs(z), eve::arg(z));
  };

  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_(KYOSU_DELAY(), O const&o, Z z) noexcept
  requires(!concepts::real<Z>)
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto [rho, theta] = to_polar(z);
      return Z(eve::log(rho), theta);
    }
    else
    {
      return _::cayley_extend(kyosu::log, z);
    }
  }

  template<concepts::cayley_dickson_like Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_(KYOSU_DELAY(), O const&o, Z z, K k) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto [r, i] = log(z);
      auto kk = eve::convert(k, as<e_t>());
      return Z(r, i+kk*two_pi(as(kk)));
    }
    else
    {
      return _::cayley_extend(kyosu::log, z, k);
    }
  }
}
