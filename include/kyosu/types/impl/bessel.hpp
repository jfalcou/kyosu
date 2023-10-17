//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <kyosu/details/cayleyify.hpp>
#include <complex>


//////////////////////////////////////////////////////////////////////////////////////////////////
//! This simd implementation of the cylindrical jn functions is inspired from
//! The codes and routines were developed and are updated by
//! <a href="https://www.researchgate.net/profile/Jhonas-de-Sarro">Jhonas O. de Sarro</a> ([@jodesarro]( https://github.com/jodesarro )).
//!
//! We repruce here the copyrith notice
//!
//!MIT License
//!
//!Copyright (c) 2021 Jhonas Olivati de Sarro
//!
//!Permission is hereby granted, free of charge, to any person obtaining a copy
//!of this software and associated documentation files (the "Software"), to deal
//!in the Software without restriction, including without limitation the rights
//!to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//!copies of the Software, and to permit persons to whom the Software is
//!furnished to do so, subject to the following conditions:
//!
//!The above copyright notice and this permission notice shall be included in all
//!copies or substantial portions of the Software.
//!
//!THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//!AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//!LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//!OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//!SOFTWARE.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_j0 = [](auto z)
        {
//          std::cout << "ascending z " << z << std::endl;
          // Ascending Series from G. N. Watson 'A treatise on the
          //  theory of Bessel functions', 2ed, Cambridge, 1996,
          //  Chapter II, equation (3); or from Equation 9.1.12 of
          //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
          //  Functions'.
          // good for abs(z) < 12
          auto eps = eve::eps(eve::as<e_t>());
          auto j0 = complex(eve::one((eve::as<e_t>())));
          auto sm = j0;
          auto test = sqr_abs(sm) >= eps*sqr_abs(j0);
          auto  m(eve::one(eve::as<e_t>()));
          auto z2 = - sqr(z);
          while(eve::any(test))
          {
            sm *= z2*e_t(0.25)/sqr(m);
            j0 = if_else(test, j0+sm, j0);
            test = sqr_abs(sm) >= eps*sqr_abs(j0);
            m = inc(m);
          }
          return j0;
        };

      auto semiconvergent_series_cyl_j0 = [saz](auto z)
        {
//          std::cout << "semi z " << z << std::endl;
          auto bound_compute = [saz]()
          {
//            std::cout << "saz " << saz << std::endl;
            auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
            bds = eve::if_else(saz < 35*35, e_t(12), bds);
//            std::cout << "bds " << bds << std::endl;
            return bds;
          };

          // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
          //  treatise on Bessel functions and their applications to
          //  physics, 1895.
          auto Pm = complex(eve::one((eve::as<e_t>())));
          auto Qm = rec(8*z);
          auto P = Pm;
          auto Q = Qm;
          auto bds = bound_compute();
          auto m = eve::one((eve::as<e_t>()));

          auto z2 = sqr(z);
           if constexpr(eve::scalar_value<e_t>)
           {
             for ( int m=1; m<=bds; m++ )
             {
               e_t pim = e_t(4*m-3)*e_t(4*m-3)*e_t(4*m-1)*e_t(4*m-1) / ( e_t(2*m-1)*e_t(128*m) );
               Pm = -Pm*pim/(z2);
               e_t xim = e_t(4*m-1)*e_t(4*m-1)*e_t(4*m+1)*e_t(4*m+1) / ( e_t(2*m+1)*e_t(128*m) );
               Qm = -Qm*xim/(z2);
               P += Pm;
               Q += Qm;
             }
             auto [s, c] = kyosu::sincos(z);
             e_t isqtpi(5.641895835477563e-01);
             auto r = isqtpi*(c*(P-Q) + s*(P+Q))/(kyosu::sqrt(z)); ;
             return r;
           }
           else
           {
            auto  bound_not_reached = m <= bds;
            while (eve::any(bound_not_reached))
            {
              auto twom = m+m;
              auto fourm = twom+twom;
              auto pim = sqr((fourm-3)*(fourm-1))/((twom-1)*128*m);
              Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
              auto xim =  sqr((fourm-1)*(fourm+1))/((twom+1)*128*m);
              Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);
              P = kyosu::if_else(bound_not_reached, P+Pm, P);
              Q = kyosu::if_else(bound_not_reached, Q+Qm, Q);
              m = inc(m);
              bound_not_reached = m <= bds;
            }
            auto [s, c] = kyosu::sincos(z);
            auto r = (c*(P-Q) + s*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
            return r;
          };
        };

      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
      auto notdone = kyosu::is_nan(r);

      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_j0, notdone, saz <= as_real_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_j0, notdone, r, z);
        }
      }
      return r;
    }
    else
    {
      return cayley_extend(cyl_bessel_j0, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_j1 = [](auto z){
        // Ascending Series from G. N. Watson 'A treatise on the
        //  theory of Bessel functions', 2ed, Cambridge, 1996,
        //  Chapter II, equation (3); or from Equation 9.1.12 of
        //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
        //  Functions'.
        // good for abs(z) < 12
        auto eps = eve::eps(eve::as<e_t>());
        auto j1 = complex(eve::one((eve::as<e_t>())));
        auto sm = j1;
        auto test = sqr_abs(sm) >= eps*sqr_abs(j1);
        auto  m(eve::one(eve::as<e_t>()));
        auto z2o_4 = - sqr(z)*e_t(0.25);
        while(eve::any(test))
        {
          sm *= z2o_4/(m*inc(m));
          j1 += sm;
          test = sqr_abs(sm) >= eps*sqr_abs(j1);
          m = inc(m);
        }
        return j1*eve::half(eve::as<e_t>())*z;
      };

      auto semiconvergent_series_cyl_j1 = [saz](auto z)
        {
          auto bound_compute = [saz]()
          {
            auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
            bds = eve::if_else(saz < 35*35, e_t(12), bds);
            return bds;
          };
          // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
          //  treatise on Bessel functions and their applications to
          //  physics, 1895.
          auto Pm = complex(eve::one((eve::as<e_t>())));
          auto Qm = -e_t(0.375)*rec(z); //-8*rec(3*z);
          auto P = Pm;
          auto Q = Qm;
          auto bds = bound_compute();
          auto m = eve::one((eve::as<e_t>()));
          auto  bound_not_reached = m <= bds;
          auto z2 = sqr(z);
          while (eve::any(bound_not_reached))
          {
            auto twom = m+m;
            auto fourm = twom+twom;
            auto pim = (4-sqr(fourm-3))*(4-sqr(fourm-1))/((twom-1)*128*m);
            Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
            auto xim =  (sqr(fourm-1)-4)*(sqr(fourm+1)-4)/((twom+1)*128*m);
            Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);
            P += Pm;
            Q += Qm;
            m = inc(m);
            bound_not_reached = m <= bds;
          }
          auto [s, c] = kyosu::sincos(z);
          return (s*(P-Q)-c*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
      };

      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto notdone = eve::true_(eve::as(saz));
      auto r = kyosu::if_else(is_eqz(saz), Z(0), eve::nan(eve::as(saz)));
      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_j1, notdone, saz <= as_real_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_j1, notdone, r, z);
        }
      }
      return if_else(rzneg, -r, r);
    }
    else
    {
      return cayley_extend(cyl_bessel_j1, z);
    }
  }

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
          return bn;
        };

        auto minus_log10_cyl_j_at_infinity = []( auto n, auto az ) {
          // Auxiliary function to calculate -log( Jn(x->INF) ).
          return e_t(0.5)*eve::log10(e_t(6.28)*n) - n*eve::log10(e_t(1.36)*az/n);
        };

        auto ini_for_br_1 = [minus_log10_cyl_j_at_infinity](auto az, auto mg)
        {
          // Starting point for backward recurrence
          //  for when |Jn(x)|~10e-mg
          //  using the secant method.
          auto n0 = inc(eve::nearest( e_t(1.1)*az));
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
          notdone = next_interval(forward, notdone, 8*n < az, r, z);
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

  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_in>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto miton = [](N n){
        if (n%4 == 0) return complex(eve::one(eve::as<e_t>()));
        else if (n%4 == 1) return  complex(eve::zero(eve::as<e_t>()), eve::mone(eve::as<e_t>()));
        else if (n%4 == 2) return complex(eve::mone(eve::as<e_t>()));
        else return complex(eve::zero(eve::as<e_t>()), eve::one(eve::as<e_t>()));
      };
      return miton(n)*cyl_bessel_jn(n,complex(-ipart(z), real(z)));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_in, n, z);
    }
  }


  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_bessel_in(0, z);
    }
    else
    {
      return cayley_extend(cyl_bessel_i0, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_bessel_in(1, z);
    }
    else
    {
      return cayley_extend(cyl_bessel_i1, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_y0 = [](auto z)
        {
          std::cout << "ascending z " << z << std::endl;
          // Ascending Series from G. N. Watson 'A treatise on the
          //  theory of Bessel functions', 2ed, Cambridge, 1996,
          //  Chapter II, equation (3); or from Equation 9.1.12 of
          //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
          //  Functions'.
          // good for abs(z) < 12
          using u_t = eve::underlying_type_t<Z>;
          auto g =eve::egamma(eve::as<u_t>());// u_t(0.5772156649015328606);
          auto twoopi= eve::two_o_pi(eve::as<u_t>());
          auto eps = eve::eps(eve::as<u_t>());
          auto hk(eve::zero(eve::as<u_t>()));
          auto z2o_4 = sqr(z*e_t(0.5));
          auto n(eve::one(eve::as<u_t>()));
          auto sgn(eve::one(eve::as<u_t>()));
          auto t = complex(eve::one ((eve::as<e_t>())));
          auto s = complex(eve::zero((eve::as<e_t>())));
          auto ds= complex(eve::zero((eve::as<e_t>())));
          auto test = sqr_abs(ds) >= eps*sqr_abs(s);

          while(eve::any(test))
          {
            std::cout << "sgn " << sgn << std::endl;
            std::cout << "nn  " << eve::sqr(n)<< std::endl;
            std::cout << "z2o_4 " << z2o_4 << std::endl;
            std::cout << "n     " << n     << std::endl;
            auto recn = rec(n);
            hk += recn;
            t *= z2o_4*sqr(recn);
            ds = hk*t;
            auto dssgn = sgn*ds;
            std::cout << "dssgn     " << dssgn  << std::endl;
            s = if_else(test, s+dssgn, s);
            std::cout  << " s " << s << std::endl;
            test = sqr_abs(ds) >= sqr(eps)*sqr_abs(s);
            n = inc(n);
            sgn = -sgn;
          }
          return ((kyosu::log(z*eve::half(eve::as<u_t>()))+g)*kyosu::cyl_bessel_j0(z)+s)*twoopi;
        };

      auto semiconvergent_series_cyl_y0 = [saz](auto z)
        {
          return z;
// //          std::cout << "semi z " << z << std::endl;
//           auto bound_compute = [saz]()
//           {
// //            std::cout << "saz " << saz << std::endl;
//             auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
//             bds = eve::if_else(saz < 35*35, e_t(12), bds);
// //            std::cout << "bds " << bds << std::endl;
//             return bds;
//           };

//           // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
//           //  treatise on Bessel functions and their applications to
//           //  physics, 1895.
//           auto Pm = complex(eve::one((eve::as<e_t>())));
//           auto Qm = rec(8*z);
//           auto P = Pm;
//           auto Q = Qm;
//           auto bds = bound_compute();
//           auto m = eve::one((eve::as<e_t>()));

//           auto z2 = sqr(z);
//            if constexpr(eve::scalar_value<e_t>)
//            {
//              for ( int m=1; m<=bds; m++ )
//              {
//                e_t pim = e_t(4*m-3)*e_t(4*m-3)*e_t(4*m-1)*e_t(4*m-1) / ( e_t(2*m-1)*e_t(128*m) );
//                Pm = -Pm*pim/(z2);
//                e_t xim = e_t(4*m-1)*e_t(4*m-1)*e_t(4*m+1)*e_t(4*m+1) / ( e_t(2*m+1)*e_t(128*m) );
//                Qm = -Qm*xim/(z2);
//                P += Pm;
//                Q += Qm;
//              }
//              auto [s, c] = kyosu::sincos(z);
//              e_t isqtpi(5.641895835477563e-01);
//              auto r = isqtpi*(c*(P-Q) + s*(P+Q))/(kyosu::sqrt(z)); ;
//              return r;
//            }
//            else
//            {
//             auto  bound_not_reached = m <= bds;
//             while (eve::any(bound_not_reached))
//             {
//               auto twom = m+m;
//               auto fourm = twom+twom;
//               auto pim = sqr((fourm-3)*(fourm-1))/((twom-1)*128*m);
//               Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
//               auto xim =  sqr((fourm-1)*(fourm+1))/((twom+1)*128*m);
//               Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);
//               P = kyosu::if_else(bound_not_reached, P+Pm, P);
//               Q = kyosu::if_else(bound_not_reached, Q+Qm, Q);
//               m = inc(m);
//               bound_not_reached = m <= bds;
//             }
//             auto [s, c] = kyosu::sincos(z);
//             auto r = (c*(P-Q) + s*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
//             return r;
//           };
        };

      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
      auto notdone = kyosu::is_nan(r);

      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_y0, notdone, saz <= as_real_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_y0, notdone, r, z);
        }
      }
      return r;
    }
    else
    {
      return cayley_extend(cyl_bessel_y0, z);
    }
  }

}
