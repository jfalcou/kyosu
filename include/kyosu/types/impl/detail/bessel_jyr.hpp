//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/types/impl/detail/bessel_jyr01.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jyr
  //===-------------------------------------------------------------------------------------------
  // here nu is always > 0 and z is at most complex
  template<eve::floating_scalar_value N, typename Z, typename R>
  auto cb_jyr( N  v, Z z, R& cjv, R& cyv) noexcept
  {
    EVE_ASSERT(is_not_flint(v), "v must not be a flint");
    int n = int(v);
    EVE_ASSERT(size(js) > n, "not enough room in js");
    EVE_ASSERT(size(ys) > n, "not enough room in ys");
    using u_t = eve::underlying_type_t<Z>;
    auto el = u_t(0.5772156649015329);
    auto rp2 = u_t( 0.63661977236758);
    auto eps = 16*eve::eps(as<u_t>());
    auto hlf = eve::half(as<u_t>());
    auto two = u_t(2);
    auto three = u_t(3);
    auto four = u_t(4);
    auto quarter = u_t(0.25);
    auto pi   = eve::pi(as<u_t>());
    auto twopi = eve::two_pi(as<u_t>());
    auto twoopi = eve::two_o_pi(as<u_t>());
    auto invpi = eve::inv_pi(as<u_t>());
    auto cspv = cbrt(eve::smallestposval(as<u_t>()));
    auto az = abs(z);
    auto z1 = z;
    auto z2 = sqr(z);
    auto v0 = frac(v); // v = n+v0 0 < v0 < 1 as v is not a flint
    auto v1 = inc(v0); // 1 < v1 < 2

    auto czero = Z{0};
    auto cone  = Z{1};
    auto cii   = i(as<Z>());

    // compute cjv0, cjv1, cyv0, cyv1;
    auto [cjv0, cyv0, cjv1, cyv1] = kyosu::_::cb_jyr01(v, z);
    cjv[0] = cjv0;
    cyv[0] = cyv0;
    cjv[1] = cjv1;
    cyv[1] = cyv1;

    if(n == 0)  return kumi::tuple{cjv0, cyv0};
    else if (n == 1) return kumi::tuple{cjv1, cyv1};
    else if (n >= 2)
    {
      // now jv0 jv1 yv0 and yv1 had been computed
      // we make forward or backward recurrence to compute the other
      auto rz = rec(z);

      auto forward = [n, v0, rz, cjv0, cjv1, &cjv](){
        // az large compared to n : 4*n <  az
        auto cf0 = cjv0;
        auto cf1 = cjv1;
        auto cf = cf1;
        for (int k=2; k<= n; ++k) {
          cf = 2*dec(k+v0)*cf1*rz-cf0;
//          if (k <= n) cjv[k] = cf;
          cf0 = cf1;
          cf1 = cf;
        }
        return cf;
      };

      auto backward = [v0, az, n, rz, cjv0, cjv1, &cjv](){
        auto m1 = ini_for_br_1(az, u_t(200));
        auto m2 = ini_for_br_2(u_t(n), az, u_t(15));
        auto m = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
        auto cf2 = Z(0);
        auto cf1 = complex(eve::sqrtsmallestposval(eve::as< u_t>()));
        auto cf = cf1;
        auto bn(cf2);

        for (int k=m; k>=0; --k)
        {
          cf = 2*inc(v0+k)*cf1*rz-cf2;
          if (k <= n) cjv[k] = cf;
          cf2 = cf1;
          cf1 = cf;
        }
        auto cs = (abs(cjv0) > abs(cjv1)) ? cjv0/cf : cjv1/cf2;
        for (int k=0; k<=n; ++k) {
          cjv[k] *= cs; ;
        }
        return cjv[n];
      };

      auto notdone = eve::true_(as<Z>());
      notdone = next_interval(forward, notdone, 4*n <= az, z);
      if( eve::any(notdone) )
      {
        last_interval(backward, notdone, z);
      }

//       auto  res_cjv =  (n <= (int)(quarter*az)) ? forward() : backward();
//       Z res_cyv;

//       auto ya0 = kyosu::abs(cyv0);
//       int lb = 0;
      auto cg0 = cyv0;
      auto cg1 = cyv1;
      for (int k=2; k<=n; ++k)
      {
        if(kyosu::abs(cjv[k-1]) > kyosu::abs(cjv[k-2]))
          cyv[k] = (cjv[k]*cyv[k-1]-2/(pi*z))/cjv[k-1];
        else
          cyv[k] = (cjv[k]*cyv[k-2]-4*dec(v0+k)/(pi*sqr(z)))/cjv[k-2];
      }
      return kumi::tuple{cjv[n], cyv[n]};
    }
  }
}
