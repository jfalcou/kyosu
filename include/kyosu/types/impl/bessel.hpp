//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <kyosu/details/cayleyify.hpp>

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
          j0 += sm;
          test = sqr_abs(sm) >= eps*sqr_abs(j0);
          m = inc(m);
        }
        return j0;
      };

      auto semiconvergent_series_cyl_j0 = [saz](auto z)
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
        auto Qm = rec(8*z);
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
          auto pim = sqr((fourm-3)*(fourm-1))/((twom-1)*128*m);
          Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
          auto xim =  sqr((fourm-1)*(fourm+1))/((twom+1)*128*m);
          Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);

          P += Pm;
          Q += Qm;
          m = inc(m);
          bound_not_reached = m <= bds;
        }
        auto [s, c] = kyosu::sincos(z);
        return (c*(P-Q) + s*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
      };

      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto notdone = eve::true_(eve::as(saz));
      auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
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
        auto z2 = - sqr(z);
        while(eve::any(test))
        {
          sm *= z2*e_t(0.25)/(m*inc(m));
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
}
