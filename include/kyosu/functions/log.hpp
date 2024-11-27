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
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct log_t : eve::elementwise_callable<log_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
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
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

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
//!      template<eve::floating_ordered_value T>     constexpr T log(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T log(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T log(T z) noexcept; //2
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
//!
//!   2. Returns elementwise the natural logarithm of the input
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
//!
//!   3. `log(z)` is semantically equivalent to `log(abs(z)) + sign(pure(z)) * arg(z)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log.cpp}
//======================================================================================================================
  inline constexpr auto log = eve::functor<log_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
