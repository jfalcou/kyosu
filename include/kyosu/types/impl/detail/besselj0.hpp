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

        Z zero{};
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
            P += if_else( bound_not_reached, Pm, zero);
            Q += if_else( bound_not_reached, Qm, zero);
          }
          bound_not_reached = u_t(++im) <= bds;
        }
        auto [s, c] = kyosu::sincos(z);
        u_t rsqrtpi = eve::rsqrt_pi(eve::as<u_t>());
        auto r = rsqrtpi*(c*(P-Q) + s*(P+Q))/(kyosu::sqrt(z));
        return r;
      };

      z = if_else(eve::is_ltz(imag(z)), -z, z);
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
      real(r) = eve::if_else(is_pure(z), eve::zero, real(r));
      return r;
    }
    else
    {
      return cayley_extend(cyl_bessel_j0, z);
    }
  }
}
