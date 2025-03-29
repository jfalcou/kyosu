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
#include <kyosu/functions/is_nan.hpp>

namespace kyosu
{
  template<typename Options>
  struct atanh_t : eve::elementwise_callable<atanh_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z> )
        return  (*this)(complex(z));
      else
        return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(atanh_t, atanh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanh
//!   @brief Computes the inverse hyperbolic tangent of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto atanh(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr auto atanh(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto atanh(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if `complex(z)` was entered.
//!
//!   2.  Returns the complex inverse hyperbolic tangent of z, in the range of a half-strip mathematically
//!       unbounded along the real axis and in the interval  \f$i\times[-\pi/2, \pi/2]\f$ along
//!       the imaginary axis.
//!
//!         * for every z: `atanh(conj(z)) == conj(atanh(z))`
//!         * for every z: `atanh(-z) == -atanh(z)`
//!         * If z is \f$+0\f$, the result is \f$+0\f$
//!         * If z is \f$NaN\f$, the result is \f$NaN\f$
//!         * If z is \f$+1\f$, the result is \f$+\infty\f$
//!         * If z is \f$x+i \infty\f$ (for any finite positive x), the result is \f$+0,\pi/2\f$
//!         * If z is \f$x+i NaN\f$ (for any finite nonzero x),  the result is \f$NaN+i NaN\f$
//!         * If z is \f$+\infty+i y\f$ (for any finite positive y),  the result is \f$i \pi/2\f$
//!         * If z is \f$+\infty+i \infty\f$, the result is \f$i \pi/2\f$
//!         * If z is \f$+\infty+i NaN\f$,  the result is \f$i NaN\f$
//!         * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!         * If z is \f$NaN+i \infty\f$, the result is \f$i \pi/2\f$ (the sign of the real part is unspecified)
//!         * If z is \f$NaN+i NaN\f$,  the result is \f$NaN+i NaN\f$
//!
//!   3. Returns \f$(\log(1+z)-\log(1-z))/2\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: atanh](https://en.cppreference.com/w/cpp/numeric/complex/atanh)
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Tangent](https://mathworld.wolfram.com/InverseHyperbolicTangent.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF: Inverse hyperbolic functions](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/atanh.cpp}
//======================================================================================================================
  inline constexpr auto atanh = eve::functor<atanh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atanh_(KYOSU_DELAY(), O const&, Z a0) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // This implementation is a simd (i.e. no branch) transcription and adaptation of the
      // boost_math code which itself is a transcription of the pseudo-code in:
      //
      // Eric W. Weisstein. "Inverse Hyperbolic Tangent."
      // From MathWorld--A Wolfram Web Resource.
      // http://mathworld.wolfram.com/InverseHyperbolicTangent.html
      //
      // Also: The Wolfram Functions Site,
      // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/
      //
      // Also "Abramowitz and Stegun. Handbook of Mathematical Functions."
      // at : http://jove.prohosting.com/~skripty/toc.htm
      //
      auto [a0r, a0i] = a0;
      auto realinf = eve::is_eqz(a0i) && eve::is_infinite(a0r);
      using rtype = decltype(a0r);
      const rtype alpha_crossover(0.3);
      auto  ltzra0 = eve::is_ltz(a0r);
      auto  ltzia0 = eve::is_ltz(a0i);
      auto s_min = eve::sqrtsmallestposval(eve::as(a0r))*2;
      auto s_max = eve::sqrtvalmax(eve::as(a0r))/2;
      rtype const two = rtype(2);
      rtype inf =  eve::inf(eve::as(a0r));
      rtype x = eve::abs(a0r);
      rtype y = eve::abs(a0i);
      auto special = eve::is_eqz(y) && (x < eve::one(eve::as(a0r)));
      auto sr = eve::atanh(a0r);
      if (eve::all(special)) {
        return complex(sr, eve::zero(eve::as(sr)));
      }

      rtype r = eve::zero(eve::as(a0r));
      rtype i = eve::zero(eve::as(a0r));
      auto gtxmax = (x > s_max);
      auto ltxmin = (x < s_min);
      auto gtymax = (y > s_max);
      auto ltymin = (y < s_min);
      rtype xx = eve::sqr(x);
      rtype yy = eve::sqr(y);
      rtype sqrabs = xx + yy;

      auto not_in_safe_zone = ((gtxmax || ltxmin) || (gtymax || ltymin));
      if(eve::any(not_in_safe_zone))
      {
        //treat underflow or overflow
        // one or both of x and y are small, calculate divisor carefully:
        rtype div = eve::one(eve::as(a0r));
        div += eve::if_else(ltxmin, xx, eve::zero);
        div += eve::if_else(ltxmin, yy, eve::zero);

        rtype alpha = x/div;
        alpha += alpha;

        auto test =  gtymax;
        // big y, medium x, divide through by y:
        rtype tmp_alpha = (two*x/y) / (y + xx/y);
        // small x and y, whatever alpha is, it's too small to calculate:
        tmp_alpha = eve::if_else(x > eve::one(eve::as(a0r)), tmp_alpha, eve::zero);
        alpha = eve::if_else(test && (x > eve::one(eve::as(a0r))), tmp_alpha, alpha);

        test =  eve::logical_andnot(gtxmax, test);

        // big x small y, as above but neglect y^2/x:
        tmp_alpha =  two/x;
        // big x: divide through by x:
        tmp_alpha =  eve::if_else((y > eve::one(eve::as(a0r))),  two / (x + y*y/x), tmp_alpha);
        // big x and y: divide alpha through by x*y:
        tmp_alpha =  eve::if_else(gtymax, (two/y) / (x/y + y/x), tmp_alpha);
        // x or y are infinite: the result is 0
        tmp_alpha = eve::if_else((y == inf) || (x == inf), eve::zero, tmp_alpha);

        alpha = eve::if_else(test, tmp_alpha, alpha);
        r = eve::if_else((alpha < alpha_crossover),
                         eve::log1p(alpha) - eve::log1p(-alpha),
                         eve::log(eve::inc(two*x + xx)) - eve::log(eve::sqr(eve::dec(x)))
                        );
        test = (x == eve::one(eve::as(a0r))) && ltymin;
        r = eve::if_else(test, -(two*(eve::log(y) - eve::log_2(eve::as(a0r)))), r);
        r *= rtype(0.25);
        //compute the imag part
        // y^2 is negligible:
        i =  eve::atan2(two*y, eve::oneminus(xx));
        i =  eve::if_else(gtymax || gtxmax, eve::pi(eve::as(a0r)), i);
        rtype tmp_i = eve::if_else(ltymin, eve::atan2(two*y, eve::one(eve::as(a0r))),
                                   eve::atan2(two*y, eve::oneminus(yy)));
        i =  eve::if_else(ltxmin, tmp_i, i);
      }
      auto test0 = (inf == x) && (inf == y);
      if(eve::any(test0))
      {
        //inf x, inf y
        r = eve::if_else(test0, eve::zero, r);
        i = eve::if_else(test0, eve::pi(eve::as(a0r)), r);
      }
      auto test = kyosu::is_nan(a0);

      if(eve::any(test))
      {
        //nan x, inf y
        r = eve::if_else(eve::is_nan(x) && (y == inf), eve::zero, r);
        i = eve::if_else(eve::is_nan(x) && (y == inf), eve::pi(eve::as(a0r)), r);

        r = eve::if_else(is_nan(y) && (x == inf), eve::zero, r);
        i = eve::if_else(is_nan(y) && (x == inf), y, i);

        r = eve::if_else(is_nan(y) && eve::is_eqz(x), eve::zero, r);
        i = eve::if_else(is_nan(y) && is_eqz(x), eve::allbits, i);
      }
      //compute for safe zone::one
      // the real part is given by:
      //
      // eve::real(atanh(z)) == eve::log((1 + x^2 + y^2 + 2x) / (1 + x^2 + y^2 - 2x))
      //
      // however, when x is either large (x > 1/e) or very small
      // (x < e) then this effectively simplifies
      // to log(1), leading to wildly inaccurate results.
      // by dividing the above (top and bottom) by (1 + x^2 + y^2) we get:
      //
      // eve::real(atanh(z)) == log((1 + (2x / (1 + x^2 + y^2))) / (1 - (-2x / (1 + x^2 + y^2))))
      //
      // which is much more sensitive to the value of x, when x is not near 1
      // (remember we can compute log(1+x) for small x very accurately).
      //
      // the cross-over from eve::one method to the other has to be determined
      // experimentally, the value used below appears correct to within a
      // factor of 2 (and there are larger errors from other parts
      // of the input domain anyway).
      //
      rtype alpha = x*two / (eve::inc(sqrabs));
      rtype sqrxm1 = eve::sqr(eve::dec(x));
      rtype tmp_r = eve::if_else((alpha < alpha_crossover),
                                 eve::log1p(alpha) - eve::log1p(-alpha),
                                 eve::log1p(x+x + sqrabs) - eve::log(sqrxm1 + yy)
                                )*rtype(0.25);
      r = eve::if_else(not_in_safe_zone, r, tmp_r);

      // compute the imag part
      i = eve::if_else(not_in_safe_zone,
                       i,
                       eve::atan2(y+y, (eve::oneminus(sqrabs)))
                      )*eve::half(eve::as(a0r));

      r = eve::if_else( ltzra0,-r, r);
      i = eve::if_else(eve::is_infinite(y), eve::pio_2(eve::as(a0r))*eve::sign(y), i);
      i = eve::if_else( ltzia0,-i, i);
      r = eve::if_else(realinf, eve::zero(eve::as(a0r)), r);
      i = eve::if_else(realinf, -eve::sign(a0r)*eve::pio_2(eve::as(a0r)), i);
      r = eve::if_else(special, sr, r);
      i = eve::if_else(special, eve::zero, i);
      return  complex(r, i);
    }
    else
    {
      return cayley_extend(atanh, a0);
    }
  }
}
