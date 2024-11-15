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
#include <kyosu/details/cayleyify.hpp>
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/functions/is_imag.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct acos_t : eve::elementwise_callable<acos_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(acos_t, acos_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acos
//!   @brief Computes the arc cosine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acos(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto atan(T z) noexcept;  //2
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
//!   1. a real typed input z is treated as if `complex(z)` was entered.
//!
//!   2. Returns elementwise the complex principal value of the arc cosine of the input.
//!      Branch cuts exist outside the interval \f$[-1, +1]\f$ along the real axis.
//!
//!      * for every z: `acos(conj(z)) == conj(acos(z))`
//!      * If z is \f$\pm0\f$, the result is \f$\pi/2\f$
//!      * If z is \f$i \textrm{\textrm{NaN}}\f$, the result is \f$\pi/2+ i \textrm{\textrm{NaN}}\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\pi/2-i\infty\f$
//!      * If z is \f$x+i \textrm{\textrm{NaN}}\f$ (for any nonzero finite x), the result is \f$\textrm{\textrm{NaN}}+i \textrm{\textrm{NaN}}\f$.
//!      * If z is \f$-\infty+i y\f$ (for any positive finite y), the result is \f$\pi-i\infty\f$
//!      * If z is \f$+\infty+i y\f$ (for any positive finite y), the result is \f$+0-i\infty\f$
//!      * If z is \f$-\infty+i +\infty\f$, the result is \f$3\pi/4-i\infty\f$
//!      * If z is \f$\infty+i +\infty\f$, the result is \f$\pi/4-i\infty\f$
//!      * If z is \f$\pm\infty+i \textrm{\textrm{NaN}}\f$, the result is \f$\textrm{\textrm{NaN}} \pm i\infty\f$ (the sign
//!        of the imaginary part is unspecified)
//!      * If z is \f$\textrm{\textrm{NaN}}+i y\f$ (for any finite y), the result is \f$\textrm{\textrm{NaN}}+i \textrm{\textrm{NaN}}\f$
//!      * If z is \f$\textrm{\textrm{NaN}}+i\infty\f$, the result is \f$\textrm{\textrm{NaN}}-i\infty\f$
//!      * If z is \f$\textrm{\textrm{NaN}}+i \textrm{\textrm{NaN}}\f$, the result is \f$\textrm{\textrm{NaN}}+i \textrm{\textrm{NaN}}\f$
//!
//!   3. Returns \f$I_z \mathrm{acosh}(z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acos.cpp}
//======================================================================================================================
  inline constexpr auto acos = eve::functor<acos_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acos_(KYOSU_DELAY(), O const&, Z a0) noexcept
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
      auto  gtzia0 = eve::is_positive(a0i);
      //
      // Begin by insuring a0r >= 0 and imag(a0) >= 0 :
      //
      rtype x = eve::abs(a0r);
      rtype y = eve::abs(a0i);
      rtype proper_real = eve::acos(x);
      auto lexone = (x <= eve::one(eve::as(x)));
      auto is_proper_real = eve::logical_and(is_real(a0), lexone);

      auto s_min = eve::sqrtsmallestposval(eve::as(x))*4;
      auto s_max = eve::sqrtvalmax(eve::as(x))/8;
      rtype xp1 = eve::inc(x);
      rtype xm1 = eve::dec(x);
      auto not_in_safe_zone = (((x > s_max) || (x < s_min)) || ((y > s_max) || (y < s_min)));
      //compute for safe zone
      rtype r, i;
      rtype yy = eve::sqr(y);
      rtype tr = eve::sqrt(eve::sqr(xp1) + yy); //hypot for pedantic ?
      rtype ts = eve::sqrt(eve::sqr(xm1) + yy); //hypot for pedantic ?
      rtype a = eve::average(tr, ts);
      rtype b = x/a;
      //compute r for b >  b_crossover
      rtype apx = a + x;
      r = eve::if_else(lexone,
                       eve::atan(eve::sqrt(eve::half(eve::as(x))*apx*(yy/(tr+xp1)+(ts-xm1)))/x),
                       eve::atan((y*eve::sqrt(eve::half(eve::as(x))*(apx/(tr+xp1)+apx/(ts+xm1))))/x)
                      );
      // r is computed
      r = eve::if_else((b <= b_crossover), eve::acos(b), r);
      //compute am1 temporary for i for a <= a_crossover
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
        auto zone1 =  (y <= eve::eps(eve::as(x))*eve::abs(xm1));
        if (eve::any(eve::logical_and(zone1, not_in_safe_zone)))
        {
          rtype rr = eve::if_else(lexone, proper_real, eve::zero);
          rtype ii = eve::if_else(lexone, y/eve::sqrt(-xp1*xm1),
                                  eve::if_else((eve::valmax(eve::as(x))/xp1 > xm1),
                                               eve::log1p(xm1 + eve::sqrt(xp1*xm1)),
                                               eve::log_2(eve::as(x)) + eve::log(x)
                                              )
                                 );
          r = eve::if_else(zone1, rr, r);
          i = eve::if_else(zone1, ii, i);
        }
        auto zone2 = (y <= s_min);
        auto not_treated = eve::logical_notand(zone1, not_in_safe_zone);
        if (eve::any(eve::logical_and(zone2, not_treated)))
        {
          rtype sqrty =  eve::sqrt(y);
          r = eve::if_else(zone2, sqrty, r);
          i = eve::if_else(zone2, sqrty, i);
        }
        auto zone3 = (eve::dec(eve::eps(eve::as(x))*y) >= x);
        not_treated = eve::logical_notand(zone2, not_treated);
        if (eve::any(eve::logical_and(zone3, not_treated)))
        {
          r = eve::if_else(zone3,  eve::pio_2(eve::as(x)), r);
          i = eve::if_else(zone3,  eve::log_2(eve::as(x)) + eve::log(y), i);
        }
        auto zone4 = (x > eve::one(eve::as(x)));
        not_treated = eve::logical_notand(zone3, not_treated);
        if (eve::any(eve::logical_and(zone4, not_treated)))
        {
          r = eve::if_else(zone4, eve::atan(y/x), r);
          i = eve::if_else(zone4, eve::log_2(eve::as(x)) + eve::log(y) + eve::half(eve::as(x))*eve::log1p(eve::sqr(x/y)), i);
        }
        not_treated = eve::logical_notand(zone4, not_treated);
        if (eve::any(not_treated))
        {
          rtype aa = eve::sqrt(eve::inc(eve::sqr(y)));
          r = eve::if_else(not_treated, eve::pio_2(eve::as(x)), r);
          i = eve::if_else(not_treated, eve::half(eve::as(x))*eve::log1p(2*y*(y+aa)), i);
        }
      }
      if (eve::any(kyosu::is_not_finite(a0)))
      {
        auto nanx = eve::is_nan(x);
        auto nany = eve::is_nan(y);
        auto infx = (x == eve::inf(eve::as(x))) ;
        auto infy = (y == eve::inf(eve::as(x))) ;
        if (eve::any(infx))
        {
          r = eve::if_else(infx, eve::zero, r);
          i = eve::if_else(infx, eve::inf(eve::as(x)), i);
          r = eve::if_else(eve::logical_and(infx, infy), eve::pio_4(eve::as(x)), r);
          i = eve::if_else(eve::logical_and(infx, infy), eve::inf(eve::as(x)), i);

          r =  eve::if_else(eve::logical_and(infx, nany), y, r);
          i =  eve::if_else(eve::logical_and(infx, nany), eve::minf(eve::as(x)), i);
        }
        if (eve::any(nanx))
        {
          r =  eve::if_else(nanx, x, r);
          i =  eve::if_else(nanx, x, i);
          i =  eve::if_else(eve::logical_and(nanx, infy), y, i);
        }
        auto test = eve::logical_notand(eve::logical_or(infx, nanx), infy);
        if (eve::any(test))
        {
          r = eve::if_else(eve::logical_and(infy, test), eve::pio_2(eve::as(x)), r);
          i = eve::if_else(eve::logical_and(infy, test), y, i);
        }
        test = eve::logical_notand(eve::logical_or(infx, nanx), nany);
        r = eve::if_else(test,eve::if_else(is_imag(a0), eve::pio_2(eve::as(x)), y), r);
        i = eve::if_else(test,y,i);
      }
      // use proper real results
      r = eve::if_else(is_proper_real, proper_real, r);
      i = eve::if_else(is_proper_real, eve::zero, i);
      // restore signs
      r = eve::if_else(ltzra0, eve::pi(eve::as(x))-r, r);
      i = eve::if_else(gtzia0, -i, i);
      return Z(r, i);
    }
    else
    {
      return cayley_extend(acos, a0);
    }
  }
}
