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
  // cyl_bessel_y0
  // cyl_bessel_y1
  /////////////////////////////////
  // utilities
  // mkjs
  // cb_j0
  // cb_j1
  // cb_y0
  // cb_y1
  ////////////////////////////////


  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  utilities
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
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
  template<typename Z> KYOSU_FORCEINLINE
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
        // good for abs(z) < 12
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

  //===-------------------------------------------------------------------------------------------
  //  cb_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
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

  //===-------------------------------------------------------------------------------------------
  //  cb_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto cb_y0(Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto egamma = eve::egamma(eve::as<u_t>());
    auto eps    = eve::eps(eve::as<u_t>());
    auto bd = bound(z);
    Z s{};
    std::cout << 2*bd-2 << std::endl;
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
  //  cb_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
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
  template<typename Z>
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
  template<typename Z>
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
  template<typename Z>
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
}
