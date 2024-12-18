//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/bessel/bessel_utils2.hpp>
#include <kyosu/details/bessel/besseln/cb_jyn.hpp>
#include <kyosu/details/bessel/besselr/cb_jyr01.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  cb_jyr
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex  Z, typename R1,  typename R2>
  auto cb_jyr( N  v, Z z, R1& cjv, R2& cyv) noexcept
  {
    int n = int(v);
    int an =  eve::abs(n);
    EVE_ASSERT(int(size(cjv)) > an, "not enough room in cjv");
    EVE_ASSERT(int(size(cyv)) > an, "not enough room in cyv");
    if (eve::is_flint(v))
    {
      return cb_jyn(int(v), z, cjv, cyv);
    }
    else if (eve::is_gtz(v))
    {
      auto v0 = eve::frac(v);  // v = n+v0 0 < v0 < 1 as v is not a flint
      // compute cjv0, cjv1, cyv0, cyv1;
      auto [cjv0, cyv0, cjv1, cyv1] = kyosu::_::cb_jyr01(v0, z);
      cjv[0] = cjv0;
      cyv[0] = cyv0;
      if (n > 0)
      {
        cjv[1] = cjv1;
        cyv[1] = cyv1;
      }
      if(n == 0)
      {
        return kumi::tuple{cjv[0], cyv[0]};
      }
      else if (n == 1)
      {
        return kumi::tuple{cjv[1], cyv[1]};
      }
      else if (n >= 2)
      {
        // now jv0 jv1 yv0 and yv1 had been computed
        // we make forward or backward recurrence to compute the others
        using u_t = eve::underlying_type_t<Z>;
        auto eps = 16*eve::eps(as<u_t>());
        auto twoopi = eve::two_o_pi(as<u_t>());
        auto az = kyosu::abs(z);
        auto z1 = z;
        auto z2 = sqr(z);
        auto v1 = inc(v0); // 1 < v1 < 2
        auto rz = rec(z);

        auto czero = Z{0};
        auto cone  = Z{1};
        auto cii   = i(as<Z>());

        auto forward = [n, v0, rz, cjv0 = cjv0, cjv1 = cjv1, &cjv](){
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

        auto backward = [czero, v0, az, n, rz, cjv0 = cjv0, cjv1 = cjv1, &cjv](){
          auto m1 = eve::maximum(ini_for_br_1(az, u_t(200)));
          auto m2 = eve::maximum(ini_for_br_2(u_t(n), az, u_t(15)));
          auto m = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
          auto cf2 = czero;
          auto cf1 = kyosu::sqrtsmallestposval(eve::as<Z>());
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
        auto notdone = kyosu::true_(as<Z>());
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
    else
    {
      // v is not flint and is less than 0;
      // we use:
      // J_{-v] = J_v(z) cos(v pi) - Y_v *sin(v pi)
      // y_{-v] = J_v(z) sin(v pi) + Y_v *cos(v pi)
      auto [jv, yv] = cb_jyr(-v, z, cjv, cyv);
      auto v0 = frac(-v);
      auto [s, c] = sinpicospi(v0);
      for(int i=0; i <= an ; ++i)
      {
        auto aa = cjv[i]*c;
        auto bb = cyv[i]*s;
        auto cc = cjv[i]*s;
        auto dd = cyv[i]*c;
        cjv[i] = aa-bb; //mulmi(a-b);
        cyv[i] = cc+dd;
        s = -s;
        c = -c;
      }
      return kumi::tuple{cjv[an], cyv[an]};
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_yr all
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, std::size_t S> KYOSU_FORCEINLINE
  auto cb_yr(N v, Z z, std::span<Z, S> vys) noexcept
  {
    auto n = std::size_t(abs(v));
    auto doit = [n, v, z, &vys](auto js, auto ys){
      auto [_, yn] = cb_jyr(v, z, js, ys);
      auto s = eve::min(size(vys), eve::inc(n));
      for(int i = 0; i < s; ++i) vys[i] = ys[i];
      return yn;
    };
    return with_alloca<Z>(n+1, doit);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_yr just last
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_yr(N v, Z z) noexcept
  {
    auto dummy = std::span<Z, 0>();
    return cb_yr(v, z,  dummy);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_jr all
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, std::size_t S> KYOSU_FORCEINLINE
  auto cb_jr(N v, Z z, std::span<Z, S> vjs) noexcept
  {
    auto n = std::size_t(abs(v));
    auto doit = [n, v, z, &vjs](auto js, auto ys){
      auto [jn, _] = cb_jyr(v, z, js, ys);
      auto s = eve::min(size(vjs), eve::inc(n));
      for(int i = 0; i < s; ++i) vjs[i] = js[i];
      return jn;
    };

    return with_alloca<Z>(n+1, doit);
  }


  //===-------------------------------------------------------------------------------------------
  //  cb_jr just last
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_jr(N v, Z z) noexcept
  {
    auto dummy = std::span<Z, 0>();
      return cb_jr(v, z,  dummy);
  }

}
