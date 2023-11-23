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
    auto  el = u_t(0.5772156649015329);
    auto  rp2 = u_t( 0.63661977236758);
    auto eps = 16*eve::eps(as<u_t>());
    auto hlf = eve::half(as<u_t>());
    auto two = u_t(2);
    auto three = u_t(3);
    auto four = u_t(4);
    auto quarter = u_t(0.25);
    auto pi   = eve::pi(as<u_t>());
    auto twopi = eve::two_pi(as<u_t>());
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
    auto initv = [](auto & t, auto val){
      for(int i=0; i < t.size ; ++i) t[i] = val;
    };
    std::vector<Z> cjv(n+1);  initv(v, czero);
    std::vector<Z> cyv(n+1);  initv(v, eve::valmax<as<u_t>());
    //    std::vector<Z> cjvp(n+1); initv(v, czero);
//     std::vector<Z> cyvp(n+1); initv(v, eve::valmin<as<u_t>());

    auto smallz =  [z, v](){
      auto ztov = pow(z*eve::half(as<u_t>()), v);

      auto jnu = ztov*eve::tgamma(inc(v));
      auto ynu = -invpi(as<u_t>())*tgamma(v)/ztov;
      return kumi::tuple(jnu, ynu);
    };

    if constexpr(eve::scalar_value<Z>)
    {
      Z cjv0, cjv1, cyv0, cyv1;
      if (az < cbrt(eve::smallestposval(as<u_t>())))
      {
        return smallz();
      }
      if(is_ltz(real(z1))) z1 = -z;
      if (az <= 12)
      {
        auto cjvO1 = [](auto vl){
          auto cjvl = cone;
          auto cr = cone;
          for (int k=1;k<=40;++k)
          {
            cr *= -0.25*z2/(k*(k+vl));
            cjvl += cr;
            if (abs(cr) < abs(cjvl)*eps) break;
          }
          auto vg = inc(vl);
          auto ga = eve::tgamma(vg);
          auto ca = pow(hlf*z1,vl)/ga;
          return ca*cjvl;
        };
        cjv0 = cjv0(v0);
        cjv1 = cjv0(inc(v0));
      }
      else
      {
        auto kz = 11;
        if (az >= 50.0) kz = 8;
        else if (az >= 35.0) kz = 10;

        auto cjyv01 = [kz](auto v0pj){
          auto vv = sqr(two*v0pj);
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
          auto z1opi = z1*invpi(as<u_t>());
          auto zk = z1opi-(hlf*(v0pj+hlf));
          auto ca0 = sqrt(two/z1);
          auto [ csk, cck] = sinpicospi(zk);
          return  kumi::tuple(ca0*(cpz*cck-cqz*csk), ca0*(cpz*csk+cqz+cck));
        };
        auto zut1 = cjyv01(v0);
        auto zut2 = cjyv01(inc(v0));
        auto [cjv0, cyv0] = zut1; //cjyv01(v0);
        auto [cjv1, cyv1] = zut2; //cjyv01(inc(v0));
      }
      if (az <= 12.0)
      {
        auto cju01 = [](auto vl){
          auto cjvl = cone;
          auto cr = cone;
          for (int k=1;k<=40;++k) {
            cr *= -quarter*z2/(k*(k-vl));
            cjvl += cr;
            if (kyosu::abs(cr) < kyosu::abs(cjvl)*eps) break;
          }
          auto vg = dec(vl);
          auto gb = gamma(vg);
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
      else {
        auto cec = log(hlf*z1)+el;
        auto cs0 = czero;
        u_t w0(0);
        auto cr0 = cone;
        for (int k=1;k<=30;++k)
        {
          w0 += u_t(1)/k;
          cr0 *= -quarter*z2/eve::sqr(k);
          cs0 += cr0*w0;
        }
        cyv0 = twopi*fms(cec, cjv0, cs0);
        auto cs1 = cone;
        u_t w1(0);
        auto cr1 = cone;
        for (int k=1;k<=30;++k)
        {
          w1 += u_t(1)/k;
          cr1 *= -quarter*z2/(k*inc(k));
          cs1 += cr1*(two*w1+u_t(1)/inc(k));
        }
        cyv1 = twopi*(cec*cjv1-rec(z1)-quarter*z1*cs1);
      }
      std::cout << cjv0 << std::endl;
      std::cout << cjv1 << std::endl;
      return kumi::tuple(v+z, v+z);
    }
    else
    {
      return kumi::tuple(v+z, v+z);
    }
  }
}
