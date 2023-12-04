//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  utilities
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  template < typename Z> struct mkjs
  {
    mkjs(size_t n, Z z):
      rz(kyosu::rec(z)),
      rs(kyosu::_:: R(n, z)),
      j(kyosu::cyl_bessel_jn(n, z)),
      i(n-1){}

    auto operator()(){
      auto pj = j;
      j = pj*rs;
      rs = 2*(i--)*rz-kyosu::rec(rs);
      return pj;
    }

    Z rz, rs, j, pj;
    int i;
  };

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_type_t<Z>;
      using u_t = eve::underlying_type_t<e_t>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_j0 = [](auto z)
        {
          // Ascending Series from G. N. Watson 'A treatise on the
          //  theory of Bessel functions', 2ed, Cambridge, 1996,
          //  Chapter II, equation (3); or from Equation 9.1.12 of
          //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
          //  Functions'.
          // good for abs(z) < 12
          auto eps2 = eve::sqr(eve::eps(eve::as<e_t>()));
          auto j0 = complex(eve::one((eve::as<e_t>())));
          auto sm = j0;
          auto test = sqr_abs(sm) >= eps2*sqr_abs(j0);
          auto  m(eve::one(eve::as<e_t>()));
          auto qz2 = - sqr(z)*u_t(0.25);
          size_t im = 1;
          while(eve::any(test))
          {
            sm *= qz2/eve::sqr(im);
            j0 +=  sm;
            test = sqr_abs(sm) >= eps2*sqr_abs(j0);
            ++im;
          }
          return j0;
        };

      auto semiconvergent_series_cyl_j0 = [saz](auto z) {
        auto bound_compute = [saz]()
        {
          auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
          bds = eve::if_else(saz < 35*35, e_t(12), bds);
          bds = eve::if_else(saz < 12*12, e_t(0),  bds);
          return bds;
        };

        // DLMF 10.17.1 Hankel expansion tabulated p[i] = a[2*i],  q[i] = a{2*i+1]
        std::array<u_t, 15> pim{1.0000000000000000e+00,
            7.0312500000000000e-02,  1.5950520833333335e+00,  5.1046874999999998e+00,  1.0609654017857142e+01,
            1.8112673611111113e+01,  2.7614701704545457e+01,  3.9116157280219781e+01,  5.2617252604166673e+01,
            6.8118106617647058e+01,  8.5618791118421058e+01,  1.0511935200216450e+02,  1.2661981997282609e+02,
            1.5012021634615385e+02,  1.7562055638227514e+02
            };
        std::array<u_t, 15> xim{1.2500000000000000e-01,
            5.8593750000000000e-01,  3.1007812499999998e+00,  7.6075148809523814e+00,  1.4111328125000002e+01,
            2.2613778409090912e+01,  3.3115484775641029e+01,  4.5616741071428571e+01,  6.0117704503676471e+01,
            7.6618466739766092e+01,  9.5119084821428572e+01,  1.1561959609683794e+02,  1.3812002604166668e+02,
            1.6262039262820511e+02,  1.8912070889778326e+02
            };
        auto rz = rec(z);
        auto rz2= sqr(rz);
        auto Pm = complex(e_t(pim[0]));
        auto Qm = rz*xim[0];
        auto P = Pm;
        auto Q = Qm;
        auto bds = bound_compute();

        size_t im = 1;
        auto  bound_not_reached = u_t(im) <= bds;
        while (eve::any(bound_not_reached))
        {
          Pm *= -pim[im]*rz2;
          Qm *= -xim[im]*rz2;
          if constexpr(eve::scalar_value<e_t>)
          {
            P += Pm;
            Q += Qm;
          }
          else
          {
            P += if_else( bound_not_reached, Pm, eve::zero);
            Q += if_else( bound_not_reached, Qm, eve::zero);
          }
          bound_not_reached = u_t(++im) <= bds;
        }
        auto [s, c] = kyosu::sincos(z);
        u_t rsqrtpi = eve::rsqrt_pi(eve::as<u_t>());
        auto r = rsqrtpi*(c*(P-Q) + s*(P+Q))/(kyosu::sqrt(z));
        return r;
      };
      auto izneg = eve::is_ltz(imag(z));
      z = if_else(izneg, conj(z), z);
      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
      auto notdone = kyosu::is_nan(r);

      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_j0, notdone, saz <= as_real_type_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_j0, notdone, r, z);
        }
      }
      imag(r) = eve::if_else(is_real(z), eve::zero, imag(r));
      r = if_else(izneg, conj(r), r);
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
      using e_t = as_real_type_t<Z>;
      using u_t = eve::underlying_type_t<e_t>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_j1 = [](auto z) {
        // Ascending Series from G. N. Watson 'A treatise on the
        //  theory of Bessel functions', 2ed, Cambridge, 1996,
        //  Chapter II, equation (3); or from Equation 9.1.12 of
        //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
        //  Functions'.
        // good for abs(z) < 12
        auto eps2 = sqr(eve::eps(eve::as<e_t>()));
        auto j1 = complex(eve::one((eve::as<e_t>())));
        auto sm = j1;
        auto test = sqr_abs(sm) >= eps2*sqr_abs(j1);
        auto  m(eve::one(eve::as<e_t>()));
        auto z2o_4 = - sqr(z)*e_t(0.25);
        while(eve::any(test))
        {
          sm *= z2o_4/(m*inc(m));
          j1 += sm;
          test = sqr_abs(sm) >= eps2*sqr_abs(j1);
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
            bds = eve::if_else(saz < 12*12, e_t(0),  bds);
            return bds;
          };

          // DLMF 10.17.1 Hankel expansion tabulated p[i] = a[2*i],  q[i] = a{2*i+1]
          std::array<u_t, 15> pim{1.0000000000000000e+00,
              -1.1718750000000000e-01,  1.2304687500000000e+00,  4.6921875000000002e+00,  1.0174386160714286e+01,
              1.7664062500000004e+01,  2.7157315340909090e+01,  3.8652558379120876e+01,  5.2149023437499999e+01,
              6.7646292892156850e+01,  8.5144120065789465e+01,  1.0464234983766234e+02,  1.2614087975543477e+02,
              1.4963963942307691e+02,  1.7513857886904762e+02
              };
          std::array<u_t, 15> xim{-3.7500000000000000e-01,
              2.7343750000000000e-01,  2.7070312500000000e+00,  7.1819196428571432e+00,  1.3668619791666668e+01,
              2.2160369318181818e+01,  3.2654747596153847e+01,  4.5150669642857139e+01,  5.9647575827205877e+01,
              7.6145148026315780e+01,  9.4643191964285705e+01,  1.1514158226284583e+02,  1.3764023437500001e+02,
              1.6213908920940170e+02,  1.8863810421798030e+02
              };
          auto rz = rec(z);
          auto rz2= sqr(rz);
          auto Pm = complex(e_t(pim[0]));
          auto Qm = complex(xim[0])*rz;
          auto P = Pm;
          auto Q = Qm;
          auto bds = bound_compute();
          size_t im = 1;
          auto  bound_not_reached = u_t(im) <= bds;

          while (eve::any(bound_not_reached))
          {
            auto m = u_t(im);
            Pm *= -pim[im]*rz2;
            Qm *= -xim[im]*rz2;
            if constexpr(eve::scalar_value<e_t>)
            {
              P += Pm;
              Q += Qm;
            }
            else
            {
              P += kyosu::if_else(bound_not_reached, Pm, eve::zero);
              Q += kyosu::if_else(bound_not_reached, Qm, eve::zero);
            }
            bound_not_reached = u_t(++im) <= bds;
          }
          auto [s, c] = kyosu::sincos(z);
          u_t rsqrtpi = eve::rsqrt_pi(eve::as<u_t>());
          auto r = rsqrtpi*(s*(P-Q) - c*(P+Q))/(kyosu::sqrt(z));
          return r;
        };

      auto izneg = eve::is_ltz(imag(z));
      z = if_else(izneg, conj(z), z);
      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
      auto notdone = kyosu::is_nan(r);

      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_j1, notdone, saz <= as_real_type_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_j1, notdone, r, z);
        }
      }
      real(r) = eve::if_else(is_pure(z), eve::zero, real(r));
      r = if_else(rzneg, -r, r);
      return  if_else(izneg, conj(r), r);
    }
    else
    {
      return cayley_extend(cyl_bessel_j1, z);
    }
  }


  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y0>, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto egamma = eve::egamma(eve::as<u_t>());
    auto eps    = eve::eps(eve::as<u_t>());
    auto bd = bound(z);
    Z s{};
    mkjs jj(2*bd-2, z);
    auto sgn =  eve::sign_alternate(u_t(bd+1));
    for (int k = bd-1; k >= 1; --k)
    {
      auto sk = sgn*jj()/k;
      jj();
      sgn = -sgn;
      s+= sk;
    }
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), twoopi*((log(z/2)+egamma)*jj()-2*s));
  }


  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y1>, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto r1 = R(1, z);
    auto y0 = cyl_bessel_y0(z);
    auto recs1 = rec(r1)-twoopi/(z*cyl_bessel_j0(z)*y0);
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), y0*recs1);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_jyn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R>
  auto cb_jyn(N nn, Z z, R& cjv, R& cyv) noexcept
  requires(concepts::complex<Z> || eve::floating_ordered_value<Z>)
  {
    EVE_ASSERT(size(js) > n, "not enough room in js");
    EVE_ASSERT(size(ys) > n, "not enough room in ys");
    using u_t = eve::underlying_type_t<Z>;
    auto n = eve::abs(nn);
    cjv[0] = cyl_bessel_j0(z);
    cyv[0] = cyl_bessel_y0(z);
    if ( is_eqz(nn) )
    {
      return kumi::tuple{cjv[0], cyv[0]};
    }
    cjv[1] = cyl_bessel_j1(z);
    cyv[1] = cyl_bessel_y1(z);
    if (nn == 1)
    {
      return kumi::tuple{cjv[1], cyv[1]};
    }
    else if (nn == -1)
    {
      cjv[1] = -cjv[1];
      cyv[1] = -cyv[1];
      return kumi::tuple{cjv[1], cyv[1]};
    }
    else
    {
     auto az = kyosu::abs(z);
      auto rz = rec(z);

      auto forwardj = [n, rz, &cjv](auto z){
        std::cout << "forwardj"<< std::endl;
        auto b0 = cjv[0];
        auto b1 = cjv[1];
        Z bn;
        for ( int k=1; k<n; ++k)
        {
          bn = 2*k*b1*rz-b0;
          cjv[k+1] = bn;
          b0 = b1;
          b1 = bn;
        }
        auto purez = is_pure(z);
        if (eve::any(purez))
        {
          for ( int k=2; k<= n; ++k) real(cjv[k]) = eve::if_else(purez, eve::zero, real(cjv[k]));
        }
        return cjv[n];
      };

      auto backwardj = [az, nn, n, &cjv](auto z){
        std::cout << "backwardj"<< std::endl;
        auto m1 = eve::maximum(ini_for_br_1(az, u_t(200)));
        auto m2 = eve::maximum(ini_for_br_2(n, az, u_t(15)));
        auto m = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
        auto cf2 = Z(0);
        auto cf1 = complex(eve::sqrtsmallestposval(eve::as< u_t>()));
        Z cf(cf2);
        int k = m;
        auto kgez = eve::is_gez(k);
        while (eve::any(kgez))
        {
          cf  = kyosu::if_else(kgez,  2*inc(k)*cf1*rec(z)-cf2, cf);
          if(k <= n && k > 1) cjv[k] = cf;
          cf2 = kyosu::if_else(kgez, cf1, cf2);
          cf1 = kyosu::if_else(kgez, cf, cf1);
          k = dec(k);
          kgez = eve::is_gez(k);
        }
        auto j0 = cjv[0];
        auto j1 = cjv[1];;
        auto fac = if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

        for(int k=2; k <= n; ++k)
        {
          cjv[k] *= fac;
          cjv[k] = nn < 0 ? cjv[k]*eve::sign_alternate(u_t(n)) : cjv[k];
          cjv[k] = if_else(eve::is_ltz(real(z)) && eve::is_odd(k), -cjv[k], cjv[k]);
        }
        return cjv[n];
      };

      auto forwardy = [az, n, nn, &cjv, &cyv](auto z){
        std::cout << "forwardy"<< std::endl;
        using u_t   =  eve::underlying_type_t<Z>;
        auto y = cyv[0];
        if (nn != 0)
        {
          int n = eve::abs(nn);
          using u_t   =  eve::underlying_type_t<Z>;
          auto twoopi = eve::two_o_pi(eve::as<u_t>());
          auto b = twoopi*rec(z);
          for(int i=1; i <= n ; ++i)
          {
            y = fms(cjv[i], y, b)/cjv[i-1];
            auto r = if_else(eve::is_gtz(real(z)) && is_real(z) && is_nan(y), complex(real(y)), y);
            r = if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), r);
            r = nn < 0 ? r*eve::sign_alternate(u_t(n)) : r;
            cyv[i] = r;
          }
          return cyv[n];
        }
        else return y;
      };
      auto z1 = z;
      auto srz = eve::signnz(real(z));
      z *= srz; //real(z) is now positive

      auto r = kyosu::if_else(is_eqz(az), Z(0), eve::nan(eve::as(az)));
      auto notdone = kyosu::is_nan(r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(forwardj, notdone, 4*n < az, r, z);
        if( eve::any(notdone) )
        {
          last_interval(backwardj, notdone, r, z);
        }
      }
      for(int i=3; i <= n; i+= 2) cjv[i] *= srz; //retablish sign for odd indices
      auto y = forwardy(z1);
      if (nn < 0)
      {
        for(int i=3; i <= n; i+= 2){
          cjv[i] *= -1; //retablish sign for odd indices
          cyv[i] *= -1; //retablish sign for odd indices
        }
        r = cjv[n];
        y = cyv[n];
      }
      return kumi::tuple{r, y};
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jyn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, kyosu::concepts::complex Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jyn>, N n, Z z, R& js, R& ys) noexcept
  {
    return cb_jyn(n, z, js, ys);
  }

}