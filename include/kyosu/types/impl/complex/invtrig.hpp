//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace kyosu::_
{
  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::asin> const&, C const& a0) noexcept
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

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acos> const&, C const& a0) noexcept
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
        rtype aa = eve::sqrt(eve::inc(sqr(y)));
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
    r = eve::if_else(is_proper_real, proper_real,   r);
    i = eve::if_else(is_proper_real, eve::zero, i);
    // restore signs
    r = eve::if_else(ltzra0, eve::pi(eve::as(x))-r, r);
    i = eve::if_else(gtzia0, -i, i);
    return complex(r, i);
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acosh> const&, C const& a0) noexcept
  {
    // acosh(a0) = +/-i acos(a0)
    // Choosing the sign of multiplier to give real(acosh(a0)) >= 0
    // we have compatibility with C99.
    auto [r, i] = kyosu::acos(a0);
    auto lez = eve::is_negative(i);;
    auto res = complex(-i, r);
    res = eve::if_else(lez, res, -res);
    auto nani = is_nan(i);
    if (eve::any(nani))
      return eve::if_else(nani && eve::is_finite(r)
                         , complex(eve::nan(eve::as(r)), eve::nan(eve::as(r)))
                         , res);
    else
      return res;
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::asinh> const&, C const& a0) noexcept
  {
    auto [r, i] = a0;
    auto [r1, i1] = kyosu::asin(complex(-i, r));
    return complex(i1, -r1); //      -(eve::i*asin(eve::i*z));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::atanh> const&, C const& a0) noexcept
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
                       eve::log(inc(two*x + xx)) - eve::log(sqr(dec(x)))
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

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::atan> const&, C const& a0) noexcept
  {

    // C99 definition here; atan(z) = -i atanh(iz):
    auto [r, i] = a0;
    auto [r1, i1] = kyosu::atanh(complex(-i, r));
    return complex(i1, -r1);
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::asec> const&, C const& z) noexcept
  {
    return kyosu::acos(kyosu::rec(z));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acsc> const&, C const& z) noexcept
  {
    return kyosu::asin(kyosu::rec(z));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::asech> const&, C const& z) noexcept
  {
    return kyosu::acosh(kyosu::rec(z));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acsch> const&, C const& z) noexcept
  {
    return kyosu::asinh(kyosu::rec(z));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acot> const&, C const& a0) noexcept
  {
    return kyosu::atan(kyosu::rec(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acoth> const&, C const& a0) noexcept
  {
    return kyosu::atanh(kyosu::rec(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acospi> const&, C const& a0) noexcept
  {
    return kyosu::radinpi(kyosu::acos(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acotpi> const&, C const& a0) noexcept
  {
    return kyosu::radinpi(kyosu::acot(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::acscpi> const&, C const& a0) noexcept
  {
    return kyosu::radinpi(kyosu::acsc(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::asecpi> const&, C const& a0) noexcept
  {
    return kyosu::radinpi(kyosu::asec(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::asinpi> const&, C const& a0) noexcept
  {
    return kyosu::radinpi(kyosu::asin(a0));
  }

  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::atanpi> const&, C const& a0) noexcept
  {
    return kyosu::radinpi(kyosu::atan(a0));
  }

}
