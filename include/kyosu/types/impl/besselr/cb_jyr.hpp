//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/types/impl/bessel/cb_jyn.hpp>
#include <kyosu/types/impl/besselr/cb_jyr01.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  cb_jy
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex  Z, typename R1,  typename R2>
  auto cb_jy( N  v, Z z, R1& cjv, R2& cyv) noexcept
  {
    int n = int(v);
    int an =  eve::abs(n);
    EVE_ASSERT(size(js) > an, "not enough room in js");
    EVE_ASSERT(size(ys) > an, "not enough room in ys");
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
    else
    {
      // v is not flint and is less than 0;
      cb_jy(-v, z, cjv, cyv);
      auto [s, c] = sinpicospi(z);
      for(int i=0; i < an ; ++i)
      {
        auto [s, c] = sinpicospi(v);
        auto a = cjv[i]*s;
        auto b = cyv[i]*c;
        cjv[i] = a-b;
        cyv[i] = a+b;
      }
      return kumi::tuple{cjv[n], cyv[n]};
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jyv
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jy>, N v, Z z, R& js, R& ys) noexcept
  {
    return cb_jy(v, z, js, ys);
  }

//   //===-------------------------------------------------------------------------------------------
//   //  cyl_bessel_jyv
//   //===-------------------------------------------------------------------------------------------
//   template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_jv>, N v, Z z, R & jv) noexcept
//   {
//      auto doit = [v, z, &jv](auto ys){
//        auto [jvn, _] = cb_jyr(eve::abs(v), z, jv, ys);
//        return kumi::tuple{jvn, _};
//      };
//      auto [jvn, _] = with_alloca<Z>(int(v)+1, doit);
//      return  jvn;
//   }

//   //===-------------------------------------------------------------------------------------------
//   //  cyl_bessel_jv
//   //===-------------------------------------------------------------------------------------------
//   template<eve::floating_scalar_value N, typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_jv>, N v, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       auto doit = [v, z](auto js, auto ys){
//         auto [jv, yv] = cb_jyr(eve::abs(v), z, js, ys);
//         return kumi::tuple{jv, yv};
//       };
//       auto n = int(v)
//       auto [jv, yv] = with_alloca<Z>(n+1, doit);
//       return  jv[n];
//     }
//     else
//     {
//       return cayley_extend_rev(cyl_bessel_jv, v, z);
//     }
//   }



}
