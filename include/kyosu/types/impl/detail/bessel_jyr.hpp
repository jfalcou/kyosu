//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_jyr.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jyr
  //===-------------------------------------------------------------------------------------------
  // here nu is always > 0 and z is at most complex
  template<eve::floating_scalar_value N, typename Z>
  auto cb_jy( N  v, Z z) noexcept
  {
    EVE_ASSERT(is_not_flint(v), "v must not be a flint");
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
    auto az = abs(z);
    auto z1 = z;
    auto z2 = sqr(z);
    int n = int(v);
    auto v0 = frac(v); // v = n+v0 0 < v0 < 1 as v is not a flint

    auto pv0 = pi*v0;
    auto pv1 = pi*inc(v0);
    auto czero = Z{0};
    auto cone  = Z{1};
    auto cii   = i(as<Z>());

    auto smallz =  [z, v, invpi, hlf](){
      auto ztov = kyosu::pow(z*hlf, v);
      auto jnu = ztov/eve::tgamma(inc(v));
      auto ynu = -invpi*tgamma(v)/ztov;
      return kumi::tuple{jnu, ynu};
    };

    if constexpr(eve::scalar_value<Z>)
    {
      if (az < cbrt(eve::smallestposval(as<u_t>())))
      {
        return smallz();
      }

      if(eve::is_ltz(real(z1))) z1 = -z;

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
        cjv1 = cjv01(inc(v0));

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
        auto cju1 = cju01(inc(v0));

        auto [s0, c0] = sincos(pv0);
        auto [s1, c1] = sincos(pv1);
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
        kumi::tie(cjv1, cyv1) = cjyv01(inc(v0));
      }
      return kumi::tuple{cjv0, cyv0};
    }
//    return kumi::tuple{cjv0, cyv0};

//       else {
//         auto cec = log(hlf*z1)+el;
//         auto cs0 = czero;
//         u_t w0(0);
//         auto cr0 = cone;
//         for (int k=1;k<=30;++k)
//         {
//           w0 += u_t(1)/k;
//           cr0 *= -quarter*z2/eve::sqr(k);
//           cs0 += cr0*w0;
//         }
//         cyv0 = twopi*fms(cec, cjv0, cs0);
//         auto cs1 = cone;
//         u_t w1(0);
//         auto cr1 = cone;
//         for (int k=1;k<=30;++k)
//         {
//           w1 += u_t(1)/k;
//           cr1 *= -quarter*z2/(k*inc(k));
//           cs1 += cr1*(two*w1+u_t(1)/inc(k));
//         }
//         cyv1 = twopi*(cec*cjv1-rec(z1)-quarter*z1*cs1);
//       }
//       std::cout << cjv0 << std::endl;
//       std::cout << cjv1 << std::endl;
//       return kumi::tuple(v+z, v+z);
//     }
//     else
//     {
//       return kumi::tuple(v+z, v+z);
//     }
  }
}
