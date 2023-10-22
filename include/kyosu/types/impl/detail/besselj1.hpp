//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
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
          auto zero = Z{};
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
              P += kyosu::if_else(bound_not_reached, Pm, zero);
              Q += kyosu::if_else(bound_not_reached, Qm, zero);
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
        notdone = next_interval(ascending_series_cyl_j1, notdone, saz <= as_real_t<Z>(144), r, z);
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
}
