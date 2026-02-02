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

namespace kyosu
{
  template<typename Options>
  struct log_t : eve::strict_elementwise_callable<log_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like  Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z>, K>
    operator()(Z const& z, K const & k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(log_t, log_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log
//!   @brief Computes the principal value of the  natural logarithm of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> log(T z eve::value n) noexcept;
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
//!       in which case the  result will the same as to an `eve::log` call
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
//!    - with two parameters return the nth branch of the logarithm.
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

  template<concepts::cayley_dickson_like Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_(KYOSU_DELAY(), O const&o, Z z) noexcept
  {
    if constexpr(O::contains(real_only) && concepts::real<Z>)
      return eve::log[o.drop(real_only)](z);
    else if constexpr(concepts::real<Z> )
      return kyosu::log[o](complex(z));
    else if constexpr(kyosu::concepts::complex<Z>)
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
  requires(!O::contains(real_only))
  {
    if constexpr(kyosu::concepts::real<Z>)
      return log[o](complex(z));
    else if constexpr(kyosu::concepts::complex<Z>)
    {
      using e_t = eve::element_type_t<decltype(real(z))>;
      auto kk = eve::convert(k, as<e_t>());
      return  log[o](z)+muli(kk*two_pi(as(kk)));
    }
    else
    {
      return _::cayley_extend(kyosu::log, z, k);
    }
  }

  template<concepts::real Z, eve::value ...K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto log_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  requires(!O::contains(real_only))
  {
    return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), log(z, k...));
  }
}
