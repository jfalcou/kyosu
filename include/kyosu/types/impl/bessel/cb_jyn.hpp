//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{
  /////////////////////////////////
  // contains implementations of
  // cyl_bessel_j0
  // cyl_bessel_j1
  // cyl_bessel_jn
  // cyl_bessel_y0
  // cyl_bessel_y1
  // cyl_bessel_yn
  // cyl_bessel_jyn
  /////////////////////////////////
  // utilities
  // mkjs
  // cb_j0
  // cb_j1
  // cb_y0
  // cb_y1
  // cbjyn
  ////////////////////////////////
  // no heap allocation is done by these functions
  // cyl_bessel_jyn computes all  j_i(z) and y_i(z) for 0 <= i <= n if n >= 0 (resp n <= i <= 0 if n <= 0)
  // and put the result in two ranges that are to be allocated by the caller.
  // call to cyl_bessel_jn and cyl_bessel_yn that need calling cyl_bessel_jyn do an internal quick allocaton
  // on the stack using __builtin_alloca_with_align.

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  utilities
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  template<eve::integral_scalar_value N, typename Z>
  Z cb_jn(N nn, Z z);

  template < typename Z> struct mkjs
  {
    mkjs(size_t n, Z z):
      rz(kyosu::rec(z)),
      rs(kyosu::_:: R(n, z)),
      j(cb_jn(n, z)),
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
  //  cb_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto cb_j0(Z z) noexcept
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
        // good for eve::abs(z) < 12
        auto eps2 = eve::sqr(eve::eps(eve::as<e_t>()));
        auto j0 = eve::one((eve::as<Z>()));
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
      auto Pm = Z(pim[0]);
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
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto cb_j1(Z z) noexcept
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
      // good for eve::abs(z) < 12
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
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto cb_y0(Z z) noexcept
  {
    auto rzlt0 = eve::is_ltz(real(z));
    auto izgt0 = eve::is_gtz(imag(z));
    z = if_else(rzlt0, -z, z);
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
    auto r = if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), twoopi*((log(z/2)+egamma)*jj()-2*s));
    if (eve::any(rzlt0))
    {
      auto sgn1 = eve::if_else(izgt0, u_t(1), u_t(-1));
      r = if_else(rzlt0, (r+2*muli(sgn1*cb_j0(z))), r);
    }
    return r;
  }


  //===-------------------------------------------------------------------------------------------
  //  cb_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto cb_y1(Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto r1 = R(1, z);
    auto y0 = cyl_bessel_y0(z);
    auto recs1 = rec(r1)-twoopi/(z*cyl_bessel_j0(z)*y0);
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), y0*recs1);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_jn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  Z cb_jn(N nn, Z z)
  {
    if ( is_eqz(nn) )
    {
      return cb_j0(z);
    }
    else if (nn == 1)
    {
      return cb_j1(z);
    }
    else if ( nn == -1 )
    {
      return -cb_j1(z);
    }
    else
    {
      using e_t = as_real_type_t<Z>;
      using u_t = eve::underlying_type_t<e_t>;
      auto n = u_t(eve::abs(nn));
      auto az = kyosu::abs(z);

      auto srz = eve::signnz(real(z));
      z *= srz;

      auto j0 = cb_j0(z);
      auto j1 = cb_j1(z);

      auto forward = [n, j0, j1](auto z){
         auto b0 = j0;
         auto b1 = j1;
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

      auto backward = [az, n, j0, j1](auto z){
        auto m1 = ini_for_br_1(az, e_t(200));
        auto m2 = ini_for_br_2(n, az, e_t(15));
        auto m = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
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
        bn *= eve::if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

        return bn;
      };
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
      r = sgnaltern(srz)*sgnaltern(n)*r;
      return nn < 0 ? r*eve::sign_alternate(u_t(nn)) : r;
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_jyn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R1, typename R2>
  auto cb_jyn(N nn, Z z, R1& cjv, R2& cyv) noexcept
  requires(concepts::complex<Z> || eve::floating_ordered_value<Z>)
  {
    auto n = eve::abs(nn);
    EVE_ASSERT(N(size(cjv)) > n, "not room enough in cjv");
    EVE_ASSERT(N(size(cyv)) > n, "not room enough in cyv");
    using u_t = eve::underlying_type_t<Z>;
    if (n <= 1)
    {
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
    }
    else
    {
      auto az = kyosu::abs(z);
      auto rzle0 = eve::is_lez(real(z));
      auto izgt0 = eve::is_gtz(imag(z));
      z = if_else(rzle0, -z, z);//real(z) is now positive
      auto rz = rec(z);
      cjv[0] = cyl_bessel_j0(z);
      cjv[1] = cyl_bessel_j1(z);
      cyv[0] = cyl_bessel_y0(z);
      cyv[1] = cyl_bessel_y1(z);

      auto forwardj = [n, rz, &cjv](auto z){
        auto bkm2 = cjv[0];
        auto bkm1 = cjv[1];
        Z bnext;
        for ( int k=2; k <= n; ++k)
        {
          auto bk =  2*(k-1)*rz*bkm1-bkm2;
          bkm2 = bkm1;
          bkm1 = bk;
          cjv[k] = bk;
        }
        auto purez = is_pure(z);
        if (eve::any(purez))
        {
          for ( int k=2; k<= n; ++k) real(cjv[k]) = eve::if_else(purez, eve::zero, real(cjv[k]));
        }
        return cjv[n];
      };

      auto backwardj = [az, nn, n, &cjv](auto z){
        auto j0 = cjv[0];
        auto j1 = cjv[1];;
        auto m1 = ini_for_br_1(az, u_t(200));
        auto m2 = ini_for_br_2(n, az, u_t(15));
        auto m0 = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
        auto m = eve::maximum(m0);
        auto cf2 = Z(0);
        auto cf1 = complex(eve::sqrtsmallestposval(eve::as<Z>()));
        Z cf(cf2);
        int k = m;
        auto kgez = eve::is_gez(k);
        while (eve::any(kgez))
        {
          cf  = kyosu::if_else(kgez&& k <= m0,  2*inc(k)*cf1*rec(z)-cf2, cf);
          if(k <= n && k > 1) cjv[k] = cf;
          cf2 = kyosu::if_else(kgez&& k <= m0, cf1, cf2);
          cf1 = kyosu::if_else(kgez&& k <= m0, cf, cf1);
          k = dec(k);
          kgez = eve::is_gez(k);
        }
        auto fac = if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

        for(int k=2; k <= n; ++k) cjv[k] *= fac;
        return cjv[n];
      };

      auto forwardy = [rz, az, n, nn, &cjv, &cyv](auto z){
        using u_t   =  eve::underlying_type_t<Z>;
        auto y = cyv[0];
        if (nn != 0)
        {
          int n = eve::abs(nn);
          using u_t   =  eve::underlying_type_t<Z>;
          auto twoopi = eve::two_o_pi(eve::as<u_t>());
          auto b = twoopi*rz;
          for(int i=1; i <= n ; ++i)
          {
            y = fms(cjv[i], y, b)/cjv[i-1];
            auto r = if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), y); //r);
            cyv[i] = r;
          }
          return cyv[n];
        }
        else return y;
      };

      // compute j2...jn for real(z) > 0
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

      // compute y2...yn for real(z) > 0
      auto y = forwardy(z);

      if (eve::any(rzle0))
      {
        // correct ys for real(z) < 0
        auto sgn0 = u_t(1);
        auto sgn1 = eve::if_else(izgt0, u_t(1), u_t(-1));
        for(int i=0; i <= n; ++i  )
        {
          cyv[i] = if_else(rzle0, sgn0*(cyv[i]+2*muli(sgn1*cjv[i])), cyv[i]);
          sgn0 = -sgn0;
        }


        // correct js for real(z) < 0
        for(int i=1; i <= n; i+= 2) cjv[i] = if_else(rzle0, -cjv[i], cjv[i]); //retablish sign for jn odd indices

        auto azne0 = is_nez(az);
        for(int i=1; i <= n; ++i  ){
          cjv[i] = if_else(azne0, cjv[i], eve::zero);
          cyv[i] = if_else(azne0, cyv[i], eve::minf(as<Z>()));
        }
      }

      if (nn < 0) //retablish sign for odd indices and negative order
      {
        for(int i=3; i <= n; i+= 2){
          cjv[i] *= -1;
          cyv[i] *= -1;
        }
      }
      return kumi::tuple{cjv[n], cyv[n]};
    }
  }


  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_j0(z);
    }
    else
    {
      return cayley_extend(cyl_bessel_j0, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_j1(z);
    }
    else
    {
      return cayley_extend(cyl_bessel_j1, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_y0(z);
    }
    else
    {
      return cayley_extend(cyl_bessel_y0, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_y1(z);
    }
    else
    {
      return cayley_extend(cyl_bessel_y1, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_jn(n, z);
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_jn, n, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jn>, N n, Z z, R& js) noexcept
  //  requires(eve::floating_ordered_value<Z> || concepts::complex<Z>)
  {
    auto doit = [n, z, &js](auto ys){
      cb_jyn(n, z, js, ys);
    };
    with_alloca<Z>(eve::abs(n)+1, doit);
    return js[n];
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_yn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_yn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto doit = [n, z](auto js, auto ys){
       auto [_, yn] =  cb_jyn(n, z, js, ys);
        return yn;
      };
      return with_alloca<Z>(eve::abs(n)+1, doit);
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_yn, n, z);
    }
  }

   //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_yn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_yn>, N n, Z z, R& ys) noexcept
  requires(eve::floating_ordered_value<Z> || concepts::complex<Z>)
  {
    auto doit = [n, z, &ys](auto js){
      cb_jyn(n, z, js, ys);
    };
    with_alloca<Z>(eve::abs(n)+1, doit);
    return ys[n];
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jyn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, kyosu::concepts::complex Z, typename R1, typename R2> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jyn>, N n, Z z, R1& js, R2& ys) noexcept
  requires(concepts::complex<Z>)
  {
    return cb_jyn(n, z, js, ys);
  }
}
