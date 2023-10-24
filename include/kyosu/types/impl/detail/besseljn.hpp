//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/besselj0.hpp>
#include <kyosu/types/impl/detail/besselj1.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jn
  //===-------------------------------------------------------------------------------------------

  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jn>, N nn, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      if ( is_eqz(nn) )
      {
        return cyl_bessel_j0(z);
      }
      else if (nn == 1)
      {
        return cyl_bessel_j1(z);
      }
      else if ( nn == -1 )
      {
        return -cyl_bessel_j1(z);
      }
      else
      {
        using e_t = as_real_t<Z>;
        using u_t = eve::underlying_type_t<e_t>;
        auto n = u_t(nn);
        auto an = eve::abs(n);
        auto az = kyosu::abs(z);

        auto forward = [n](auto z){
          auto b0 = cyl_bessel_j0(z);
          auto b1 = cyl_bessel_j1(z);
          Z bn;
          auto rz = rec(z);
          for ( int k=1; k<n; ++k)
          {
            bn = 2*k*b1*rz-b0;
            b0 = b1;
            b1 = bn;
          }
          real(bn) = eve::if_else(is_pure(z), eve::zero, real(bn));
          return bn;
        };

        auto minus_log10_cyl_j_at_infinity = []( auto n, auto az ) {
          // Auxiliary function to calculate -log( Jn(x->INF) ).
          return u_t(0.5)*eve::log10(u_t(6.28)*n) - n*eve::log10(u_t(1.36)*az/n);
        };

        auto ini_for_br_1 = [minus_log10_cyl_j_at_infinity](auto az, auto mg)
        {
          // Starting point for backward recurrence
          //  for when |Jn(x)|~10e-mg
          //  using the secant method.
          auto n0 = inc(eve::nearest( u_t(1.1)*az));
          auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - mg;
          auto n1 = n0 + 5;
          auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - mg;
          auto nn = n1 - (n1 - n0)/oneminus(f0/f1);
          auto f = minus_log10_cyl_j_at_infinity(nn, az) - mg;
          auto test = eve::abs(nn - n1) > 1;
          while ( eve::any(test) )
          {
            n0 = n1;
            f0 = f1;
            n1 = nn;
            f1 = f;
            nn = eve::if_else(test, n1 - (n1 - n0)/oneminus(f0/f1), nn);
            f =  eve::if_else(test, minus_log10_cyl_j_at_infinity(nn, az) - mg, f);
            test =  eve::abs(nn - n1) > 1;
          }
          return eve::trunc(nn);
        };

        auto ini_for_br_2 = [minus_log10_cyl_j_at_infinity](auto n, auto az, auto sd){
          // Starting point for backward recurrence
          //  for when Jn(x) has sd significant digits
          //  using the secant method.
          auto hmp = eve::half(eve::as<e_t>())*sd;
          auto ejn = minus_log10_cyl_j_at_infinity(n, az);
          auto t = ejn <= hmp;
          auto obj = eve::if_else(t, sd, hmp+ejn);
          auto n0  = eve::if_else(t, eve::nearest(e_t(1.1)*az), n);
          auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - obj;
          auto n1 = n0 + 5;
          auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - obj;
          auto nn = n1 - (n1-n0)/oneminus(f0/f1);
          auto f = minus_log10_cyl_j_at_infinity(nn, az) - obj;
          auto test = eve::abs(nn - n1) >= 1;
          while ( eve::any(test))
          {
            n0 = n1;
            f0 = f1;
            n1 = nn;
            f1 = f;
            nn = eve::if_else(test, n1 - (n1-n0)/(oneminus(f0/f1)), nn);
            f  = eve::if_else(test, minus_log10_cyl_j_at_infinity(nn, az) - obj, f);
            test = eve::abs(nn - n1) >= 1;
          }
          return eve::trunc(nn + 10);
        };

        auto backward = [az, n, ini_for_br_1, ini_for_br_2](auto z){
          auto m = ini_for_br_1(az, e_t(200));
          m = eve::if_else ( m >= n, ini_for_br_2(n, az, e_t(15)), m);
          auto cf2 = Z(0);
          auto cf1 = complex(eve::sqrtsmallestposval(eve::as< e_t>()));
          Z cf(cf2);
          Z bn(cf);
          auto k = m;
          auto kgez = eve::is_gez(k);
          while (eve::any(kgez))
          {
            cf  = kyosu::if_else(kgez,  2*inc(k)*cf1*rec(z)-cf2, cf);
            bn  = kyosu::if_else ( k == n, cf, bn);
            cf2 = kyosu::if_else(kgez, cf1, cf2);
            cf1 = kyosu::if_else(kgez, cf, cf1);
            k = dec(k);
            kgez = eve::is_gez(k);
          }
          auto j0 = cyl_bessel_j0(z);
          auto j1 = cyl_bessel_j1(z);
          bn *= eve::if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

          return bn;
        };

        auto srz = eve::signnz(real(z));
        z *= srz;

        auto r = kyosu::if_else(is_eqz(az), Z(0), eve::nan(eve::as(az)));
        auto notdone = kyosu::is_nan(r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(forward, notdone, 4*n < az, r, z);
          if( eve::any(notdone) )
          {
            last_interval(backward, notdone, r, z);
          }
        }
        auto sgnaltern = [n](auto x){return eve::if_else(eve::is_ltz(x), eve::one, eve::sign_alternate(n));};
        return sgnaltern(srz)*sgnaltern(n)*r;
      }
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_jn, nn, z);
    }
  }

}
