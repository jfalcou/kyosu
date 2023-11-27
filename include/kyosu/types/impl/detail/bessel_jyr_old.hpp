//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_utils2.hpp>

//#include <kyosu/types/impl/detail/bessel_jyr.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jyr
  //===-------------------------------------------------------------------------------------------
  // here nu is always > 0 and z is at most complex
  template<eve::floating_scalar_value N, typename Z, typename R>
  auto cb_jy( N  v, Z z, R& cjv, R& cyv) noexcept
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

    auto smallz =  [z, v0, v1, n, invpi, hlf, &cjv, &cyv](){
      // DLMF 10.7.3 and 10.7.4
      auto lzh = kyosu::log(z*hlf);
      auto vk = v0;
      auto lgvk = log_gamma(v0);
      for(int k=0; k <= n; ++k)
      {
        auto lzhtovk = lzh*vk;
        auto lgvkp1 = lgvk+log(vk);
        cjv[k] = kyosu::exp(lzhtovk-lgvkp1);
        cyv[k] = -invpi*kyosu::exp(lgvk-lzhtovk);
        lgvk = lgvkp1;
        vk = inc(vk);
      }
      return kumi::tuple{cjv[n], cyv[n]};
    };

    if constexpr(eve::scalar_value<Z>)
    {
      if (az < cspv)
      {
        return smallz();
      }

//      if(eve::is_ltz(real(z1))) z1 = -z;

      Z cjv0, cjv1, cyv0, cyv1;
      if (az <= 12)
      {
        auto cjv01 = [quarter, hlf, cone, eps, z1, z2](auto vl){
          auto cjvl = cone;
          auto cr = cone;
          for (int k=1;k<=40;++k)
          {
            cr *= -quarter*z2/(k*(k+vl));
            cjvl += cr;
            if (abs(cr) < abs(cjvl)*eps) break;
          }
          auto vg = inc(vl);
          auto ga = eve::tgamma(vg);
          auto ca = pow(hlf*z1,vl)/ga;
          return ca*cjvl;
        };
        cjv0 = cjv01(v0);
        cjv1 = cjv01(v1);

        auto cju01 = [two, cone, quarter, eps, z1, z2](auto vl){
          auto cjvl = cone;
          auto cr = cone;
          for (int k=1;k<=40;++k) {
            cr *= -quarter*z2/(k*(k-vl));
            cjvl += cr;
            if (kyosu::abs(cr) < kyosu::abs(cjvl)*eps) break;
          }
          auto vg = eve::oneminus(vl);
          auto gb = eve::tgamma(vg);
          auto cb = pow(two/z1,vl)/gb;
          return cjvl*cb;
        };
        auto cju0 = cju01(v0);
        auto cju1 = cju01(v1);

        auto [s0, c0] = sinpicospi(v0);
        auto [s1, c1] = sinpicospi(v1);
        cyv0 = fms(cjv0, c0, cju0)/s0;
        cyv1 = fms(cjv1, c1, cju1)/s1;
      }
      else
      {
        auto kz = 11;
        if (az >= 35.0) kz = 10;
        else if (az >= 50.0) kz = 8;

        auto cjyv01 = [twoopi, pi, quarter, hlf, three, two, cone, four, invpi, kz, z1, z2](auto v0p){
          auto vv = sqr(two*v0p);
          auto cpz = cone;
          auto crp = cone;
          for (int k=1;k<=kz;++k)
          {
            crp = u_t(-0.78125e-2)*crp*(vv-sqr(four*k-three))*
              (vv-sqr(dec(four*k)))/(k*dec(two*k)*z2);
            cpz += crp;
          }
          auto cqz = cone;
          auto crq = cone;
          for (int k=1;k<=kz;++k)
          {
            crq = u_t(-0.78125e-2)*crq*(vv-sqr(dec(four*k)))*
              (vv-sqr(inc(four*k)))/(k*inc(two*k)*z2);
            cqz += crq;
          }
          cqz *= u_t(0.125)*dec(vv)/z1;
          auto z1opi = z1*invpi;
          auto zk = z1opi-(hlf*(v0p+hlf));
          auto ca0 = sqrt(twoopi/z1);
          auto [ csk, cck] = sinpicospi(zk);
          return  kumi::tuple{ca0*(cpz*cck-cqz*csk)
              , ca0*(cpz*csk+cqz*cck)};
        };
        kumi::tie(cjv0, cyv0) = cjyv01(v0);
        kumi::tie(cjv1, cyv1) = cjyv01(v1);
      }

//       if (real(z) < 0.0) {
//         std::cout << "icitte" << std::endl;
//         auto cfac0 = exp_ipi(v0);
//         auto cfac1 = exp_ipi(v1);
//         auto rcfac0= rec(cfac0);
//         auto rcfac1= rec(cfac1);
//         auto icospv0 = 2*muli(cospi(v0));
//         auto icospv1 = 2*muli(cospi(v1));
//         if (imag(z) < 0.0) {
//           cyv0 = cfac0*cyv0-icospv0*cjv0;
//           cyv1 = cfac1*cyv1-icospv1*cjv1;
//           cjv0 *= rcfac0;
//           cjv1 *= rcfac1;
//         }
//         else if (imag(z) > 0.0) {
//           cyv0 = cyv0*rcfac0+icospv0*cjv0;
//           cyv1 = cyv1*rcfac1+icospv1*cjv1;
//           cjv0 *= cfac0;
//           cjv1 *= cfac1;
//         }
//       }

//       std::cout<< std::endl << "besselj(" << v0 << ") = " << cjv0 << std::endl;
//       std::cout<< std::endl << "besselj(" << v0+1 << ") = " << cjv1 << std::endl;

      // now jv0 jv1 yv0 and yv1 had been computed
      // we make forward or backward recurrence
      cjv[0] = cjv0;
      cyv[0] = cyv0;
      cjv[1] = cjv1;
      cyv[1] = cyv1;

      if(n == 0)  return kumi::tuple{cjv0, cyv0};
      else if (n == 1) return kumi::tuple{cjv1, cyv1};
      else if (n >= 2)
      {
        auto rz = rec(z);


        auto forward = [n, v0, rz, cjv0, cjv1, &cjv](){
          // az large compared to n : 4*n <  az
          auto cf0 = cjv0;
          auto cf1 = cjv1;
          auto cf = cf1;
          for (int k=2; k<= n; ++k) {
            cf = 2*dec(k+v0)*cf1*rz-cf0;
            if (k <= n) cjv[k] = cf;
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
        auto  res_cjv =  (n <= (int)(quarter*az)) ? forward() : backward();
        Z res_cyv;

        auto ya0 = kyosu::abs(cyv0);
        int lb = 0;
        auto cg0 = cyv0;
        auto cg1 = cyv1;
        for (int k=2; k<=n; ++k)
        {
          if(kyosu::abs(cjv[k-1]) > kyosu::abs(cjv[k-2]))
            cyv[k] = (cjv[k]*cyv[k-1]-2/(pi*z))/cjv[k-1];
          else
            cyv[k] = (cjv[k]*cyv[k-2]-4*dec(v0+k)/(pi*sqr(z)))/cjv[k-2];
        }
        return kumi::tuple{res_cjv, cyv[n]};
      }
    }
  }
}
