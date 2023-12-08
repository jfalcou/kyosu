//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/types/impl/detail/bessel_jy.hpp>
#include <kyosu/types/impl/detail/bessel_jyr01.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  cb_jyr
  //===-------------------------------------------------------------------------------------------
  // here nu is always > 0 and z is at most complex
  template<eve::floating_scalar_value N, typename Z, typename R>
  auto cb_jyr( N  v, Z z, R& cjv, R& cyv) noexcept
  {
    EVE_ASSERT(is_not_flint(v), "v must not be a flint");
    int n = int(v);
    EVE_ASSERT(size(cjv) > n, "not enough room in js");
    EVE_ASSERT(size(cyv) > n, "not enough room in ys");
    auto v0 = frac(v);  // v = n+v0 0 < v0 < 1 as v is not a flint
    // compute cjv0, cjv1, cyv0, cyv1;
    auto [cjv0, cyv0, cjv1, cyv1] = kyosu::_::cb_jyr01(v0, z);
    cjv[0] = cjv0;
    cyv[0] = cyv0;
    if (n > 0)
    {
      cjv[1] = cjv1;
      cyv[1] = cyv1;
    }
    if(n == 0)  {
      return kumi::tuple{cjv0, cyv0};
    }
    else if (n == 1)
    {
      return kumi::tuple{cjv1, cyv1};
    }
    else if (n >= 2)
    {
      // now jv0 jv1 yv0 and yv1 had been computed
      // we make forward or backward recurrence to compute the others
      using u_t = eve::underlying_type_t<Z>;
      auto eps = 16*eve::eps(as<u_t>());
      auto twoopi = eve::two_o_pi(as<u_t>());
      auto az = abs(z);
      auto z1 = z;
      auto z2 = sqr(z);
      auto v1 = inc(v0); // 1 < v1 < 2
      auto rz = rec(z);

      auto czero = Z{0};
      auto cone  = Z{1};
      auto cii   = i(as<Z>());

      auto forward = [n, v0, rz, cjv0, cjv1, &cjv](){
        // az large compared to n : 4*n <  az
        auto cf0 = cjv0;
        auto cf1 = cjv1;
        auto cf = cf1;
        for (int k=2; k <= n; ++k) {
          cf = 2*dec(k+v0)*cf1*rz-cf0;
          cjv[k] = cf;
          cf0 = cf1;
          cf1 = cf;
        }
        return cf;
      };

      auto backward = [czero, v0, az, n, rz, cjv0, cjv1, &cjv](){
        auto m1 = eve::maximum(ini_for_br_1(az, u_t(200)));
        auto m2 = eve::maximum(ini_for_br_2(u_t(n), az, u_t(15)));
        auto m = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
        auto cf2 = czero;
        auto cf1 = eve::sqrtsmallestposval(eve::as<Z>());
        auto cf = cf1;
        auto bn(cf2);

        for (int k=m; k>=0; --k)
        {
          cf = u_t(2)*inc(v0+u_t(k))*cf1*rz-cf2;
          if (k <= n) cjv[k] = cf;
          cf2 = cf1;
          cf1 = cf;
        }
        auto cs = if_else(abs(cjv0) > abs(cjv1), cjv0/cf, cjv1/cf2);
        for (int k=0; k<=n; ++k) {
          cjv[k] *= cs; ;
        }
        return cjv[n];
      };
      // compute j_{v+i} i =  2...n
      Z r;
      auto notdone = eve::true_(as<Z>());
      notdone = next_interval(forward, notdone, 4*n <= az, r);
      if( eve::any(notdone) )
      {
        last_interval(backward, notdone, r);
      }
      // compute y_{v+i} i =  2...n
      auto twoopiz = twoopi*rz;
      auto fouropisqz = 2*twoopiz*rz;
      for (int k=2; k<=n; ++k)
      {
        cyv[k] = if_else(kyosu::abs(cjv[k-1]) > kyosu::abs(cjv[k-2])
                        , (cjv[k]*cyv[k-1]-twoopiz)/cjv[k-1]
                        , (cjv[k]*cyv[k-2]-dec(v0+k)*fouropisqz)/cjv[k-2]
                        );
      }
      return kumi::tuple{cjv[n], cyv[n]};
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jy
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jy>, N v, Z z, R& js, R& ys) noexcept
  {
    if (is_flint(v))
      return cb_jyn(int(v), z, js, ys);
    else
      return cb_jyr(v, z, js, ys);
  }

}
