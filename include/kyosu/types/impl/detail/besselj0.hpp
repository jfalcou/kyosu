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
  //  cyl_bessel_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      using u_t = eve::underlying_type_t<e_t>;
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
//          std::cout << "ascending" << std::endl;
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
            auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
            bds = eve::if_else(saz < 35*35, e_t(12), bds);
            bds = eve::if_else(saz < 12*12, e_t(0),  bds);
//            std::cout << "bds " << bds << std::endl;
            return bds;
          };

          // DLMF 10.17.1 Hankel expansion tabulated p[i] = a[2i],  q[i] = a{2i°1]
          std::array<u_t, 15> p{1.0000000000000000e+00,
              -7.0312500000000000e-02,  1.1215209960937500e-01,  -5.7250142097473145e-01,  6.0740420012734830e+00,
              -1.1001714026924674e+02,  3.0380905109223841e+03,  -1.1883842625678323e+05,  6.2529514934347952e+06,
              -4.2593921650476676e+08,  3.6468400807065552e+10,  -3.8335346613939438e+12,  4.8540146868528994e+14,
              -7.2868573493776544e+16,  1.2797219419759741e+19
              };
          std::array<u_t, 15> q{1.2500000000000000e-01,
              -7.3242187500000000e-02,  2.2710800170898438e-01,  -1.7277275025844574e+00,  2.4380529699556064e+01,
              -5.5133589612202059e+02,  1.8257755474293172e+04,  -8.3285930401628907e+05,  5.0069589531988911e+07,
              -3.8362551802304325e+09,  3.6490108188498328e+11,  -4.2189715702840953e+13,  5.8272446315669060e+15,
              -9.4762880992601062e+17,  1.7921623230516983e+20
              };

          // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
          //  treatise on Bessel functions and their applications to
          //  physics, 1895.
          //
//          std::cout << "semi" << std::endl;
          if constexpr(eve::scalar_value<e_t>)
          {
//            std::cout << "icitte" << std::endl;
            u_t sgn(-1);
            auto P = complex(u_t(p[0]));
            auto Q = complex(u_t(q[0]));
            auto rz = rec(z);
            auto rz2 = sqr(rz);
            size_t bds = bound_compute();
            auto x = rz2;
            for ( size_t m=1; m<=bds; ++m )
            {
              P+= sgn*p[m]*x;
              Q+= sgn*q[m]*x;
              x*= rz2;
//              sgn = -sgn;
            }
            Q*= rz;
            auto pio4 = eve::pio_4(eve::as<u_t>());
            auto [s, c] = kyosu::sincos(z-pio4);
            e_t isqtpio2(0.797884560802865);
            auto r = isqtpio2*(c*P-s*Q)/(kyosu::sqrt(z)); ;
            return r;
          }
          else
          {
            //            std::cout << "latte" << std::endl;
            auto zero = complex(u_t(0));
            auto Pm = complex(e_t(p[0]));
            auto Qm = complex(e_t(q[0]));
            auto rz = rec(z);
            auto rz2 = sqr(rz);
            auto P = Pm;
            auto Q = Qm;
            auto bds = bound_compute();
            //           std::cout << "bds " << bds << std::endl;
            size_t im = 1;
            auto  bound_not_reached = u_t(im) <= bds;
            while (eve::any(bound_not_reached))
            {
//              std::cout << "im " << im << std::endl;
              Pm *= kyosu::if_else(bound_not_reached, -Pm*p[im]*rz2, zero);
              Qm *= kyosu::if_else(bound_not_reached, -Qm*q[im]*rz2, zero);
              P += Pm;
              Q += Qm;
              im = inc(im);
              bound_not_reached = u_t(im) <= bds;
            }
            Q *= rec(z);
            auto [s, c] = kyosu::sincos(z);
            e_t isqtpi(5.641895835477563e-01);
            auto r = isqtpi*(c*(P+Q) + s*(P-Q))/(kyosu::sqrt(z)); ;
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
}
