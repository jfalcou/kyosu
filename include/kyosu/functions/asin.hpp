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
  struct asin_t : eve::elementwise_callable<asin_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return  KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(asin_t, asin_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asin
//!   @brief Computes the arcsine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto asin(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto asin(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acos(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns the elementwise the complex principal value
//!      of the arc sine of the input in the range of a strip unbounded along the imaginary axis
//!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
//!
//!      special cases are handled as if the operation was implemented by \f$-i\; \mathrm{asinh}(z\; i)\f$
//!
//!   3. Returns \f$-I_z \mathrm{asinh}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asin.cpp}
//======================================================================================================================
  inline constexpr auto asin = eve::functor<asin_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asin_(KYOSU_DELAY(), O const&, Z a0) noexcept
  {
     if constexpr(concepts::complex<Z> )
    {
      // This implementation is a simd transcription and adaptation of the boost_math code
      // which itself is a transcription of the pseudo-code in:
      //
      // "Implementing the complex Arcsine and Arccosine Functions using Exception Handling."
      // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
      // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
      //
      auto [a0r, a0i] = a0;
      using rtype = decltype(a0r);
      const rtype a_crossover(1.5);
      const rtype b_crossover(0.6417);
      auto  ltzra0 = eve::is_negative(a0r);
      auto  ltzia0 = eve::is_negative(a0i);

      //
      // Begin by insuring real(a0) >= 0 and imag(a0) >= 0 :
      //

      rtype x = eve::abs(a0r);
      rtype y = eve::abs(a0i);
      rtype proper_real = eve::asin(x);
      auto lexone = (x <= eve::one(eve::as(a0r)));
      auto is_proper_real = is_real(a0) && lexone;

      auto s_min = eve::sqrtsmallestposval(eve::as(x))*4;
      auto s_max = eve::sqrtvalmax(eve::as(x))/8;
      rtype xp1 =  eve::inc(x);
      rtype xm1 =  eve::dec(x);
      auto not_in_safe_zone = (((x > s_max) || (x < s_min)) || ((y > s_max) || (y < s_min)));
      //compute for safe zone
      rtype r, i;
      rtype yy = eve::sqr(y);
      rtype tr = eve::sqrt(eve::sqr(xp1) + yy);//hypot for pedantic ?
      rtype ts = eve::sqrt(eve::sqr(xm1) + yy);//hypot for pedantic ?
      rtype a = eve::average(tr, ts);
      rtype b = x/a;
      //compute r for b >  b_crossover
      rtype apx = a + x;
      r = eve::if_else(lexone,
                       eve::atan(x/eve::sqrt(eve::half(eve::as(a0r))*apx*(yy/(tr+xp1)+(ts-xm1)))),
                       eve::atan(x/(y*eve::sqrt(eve::half(eve::as(a0r))*(apx/(tr+xp1)+apx/(ts+xm1)))))
                      );
      // r is computed
      r = eve::if_else((b <= b_crossover), r, eve::asin(b));
      //compute am 1 temporary for i for a <= a_crossover
      rtype tmp = yy/(tr+xp1);
      rtype am1 = eve::if_else(lexone,
                               eve::average(tmp, yy/(ts-xm1)),
                               eve::average(tmp, (ts+xm1)));
      i =  eve::if_else((a <= a_crossover),
                        eve::log1p(am1 + eve::sqrt(am1*(eve::inc(a)))),
                        eve::log(a + eve::sqrt(eve::dec(eve::sqr(a))))
                       );
      // i is computed
      //compute for exception zone
      if (eve::any(not_in_safe_zone))
      {
        auto zone1 =  (y <= eve::eps(eve::as(a0r))*eve::abs(xm1));
        if (eve::any(eve::logical_and(zone1, not_in_safe_zone)))
        {
          rtype rr = eve::if_else(lexone, eve::asin(x), eve::pio_2(eve::as(a0r)));
          rtype ii = eve::if_else(lexone, y/eve::sqrt(xp1*xm1),
                                  eve::if_else((eve::valmax(eve::as(a0r))/xp1 > xm1),
                                               eve::log1p(xm1 + eve::sqrt(xp1*xm1)),
                                               eve::log_2(eve::as(a0r)) + eve::log(x)
                                              )
                                 );
          r = eve::if_else(zone1, rr, r);
          i = eve::if_else(zone1, ii, i);
        }
        auto zone2 = (y <= s_min);
        auto not_treated = eve::logical_notand(zone1, not_in_safe_zone);
        if (eve::any(eve::logical_and(zone2, not_treated)))
        {
          r = eve::if_else(zone2, eve::pio_2(eve::as(a0r)) - eve::sqrt(y), r);
          i = eve::if_else(zone2, eve::sqrt(y), i);
        }
        auto zone3 = (eve::dec(eve::eps(eve::as(a0r))*y) >= x);
        not_treated = eve::logical_notand(zone2, not_treated);
        if (eve::any(eve::logical_and(zone3, not_treated)))
        {
          r = eve::if_else(zone3,  x/y, r);
          i = eve::if_else(zone3,  eve::log_2(eve::as(a0r)) + eve::log(y), i);
        }
        auto zone4 = (x > eve::one(eve::as(a0r)));
        not_treated = eve::logical_notand(zone3, not_treated);
        if (eve::any(eve::logical_and(zone4, not_treated)))
        {
          r = eve::if_else(zone4, eve::atan(x/y), r);
          i = eve::if_else(zone4, eve::log_2(eve::as(a0r)) + eve::log(y)
                           + eve::half(eve::as(a0r))*eve::log1p(eve::sqr(x/y)), i);
        }
        not_treated = eve::logical_notand(zone4, not_treated);
        if (eve::any(not_treated))
        {
          rtype aa = eve::sqrt(eve::inc(eve::sqr(y)));
          r = eve::if_else(not_treated, x/aa, r);
          i = eve::if_else(not_treated,eve::half(eve::as(a0r))*eve::log1p(2*y*(y+aa)), i);
        }
      }
      if (eve::any(is_not_finite(a0)))
      {
        auto nanx = eve::is_nan(x);
        auto nany = eve::is_nan(y);
        auto infx = (x == eve::inf(eve::as(a0r))) ;
        auto infy = (y == eve::inf(eve::as(a0r))) ;
        if (eve::any(nanx))
        {
          r =  eve::if_else(nanx, x, r);
          r =  eve::if_else(nanx && infy, x, r);
          i =  eve::if_else(nanx, x, i);
          i =  eve::if_else(nanx && infy, y, i);
        }
        if (eve::any(nany))
        {
          auto isimag = is_imag(a0);
          r =  eve::if_else(isimag && nany, eve::zero, r);
          r =  eve::if_else(eve::logical_and(nany, infx),y, r);
          i =  eve::if_else(isimag && nany, eve::allbits, i);
          i =  eve::if_else(nany && infx, x, i);
        }
        auto test = eve::logical_notand(eve::logical_or(nanx, nany), infx);
        if (eve::any(test))
        {
          r = eve::if_else(infx && test,
                           eve::if_else(infy, eve::pio_4(eve::as(a0r)), eve::pio_2(eve::as(a0r))),
                           r);
        }
        test = eve::logical_notand(eve::is_nan(x) || eve::is_nan(y),
                                   eve::logical_andnot(infy, infx));
        r = eve::if_else(test,eve::zero,r);
      }
      // use proper real results

      r = eve::if_else(is_proper_real, proper_real,   r);
      i = eve::if_else(is_proper_real, eve::zero, i);
      // restore signs
      r = eve::if_else(ltzra0, -r, r);
      i = eve::if_else(ltzia0, -i, i);
      return complex(r, i);
    }
    else
    {
      return cayley_extend(asin, a0);
    }
  }
}
