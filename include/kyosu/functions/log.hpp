//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct log_t : eve::elementwise_callable<log_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>) return (*this)(complex(z));
      else                            return KYOSU_CALL(z);
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T log(T z) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!    - A real typed input z is treated as if `complex(z)` was entered.
//!    - For complex entry  Returns elementwise the natural logarithm of the input
//!      in the range of a strip in the interval \f$i\times[-\pi, \pi]\f$ along the imaginary axis
//!      and mathematically unbounded along the real axis. .
//!
//!      * The function is continuous onto the branch cut  along the negative real axis,
//!        taking into account the sign of imaginary part
//!      * for every z: `log(conj(z)) == :conj(log(z))`
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
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z log_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto arg = [](auto zz){ return eve::atan2[eve::pedantic](kyosu::imag(zz), kyosu::real(zz));};
      auto [rz, iz] = z;
      auto infty = eve::inf(eve::as(rz));
      auto argz = arg(z);
      auto absz = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz), infty, kyosu::abs(z));
      auto la = eve::log(absz);
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), complex(la), complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      return _::cayley_extend(kyosu::log, z);
    }
  }
}
