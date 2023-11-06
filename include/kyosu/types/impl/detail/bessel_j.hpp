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
      auto izneg = eve::is_ltz(imag(z));
      z = if_else(izneg, conj(z), z);
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

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jn
  //===-------------------------------------------------------------------------------------------
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
        auto n = u_t(eve::abs(nn));
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
          real(bn) = eve::if_else(is_pure(z), eve::zero, real(bn));
          return bn;
        };

        auto minus_log10_cyl_j_at_infinity = []( auto n, auto az ) {
          // Auxiliary function to calculate -log( Jn(x->INF) ).
          return u_t(0.5)*eve::log10(u_t(6.28)*n) - n*eve::log10(u_t(1.36)*az/n);
        };

        auto ini_for_br_1 = [minus_log10_cyl_j_at_infinity](auto az, auto mg)
          {
            // Starting point for backward recurrence
            //  for when |Jn(x)|~10e-mg
            //  using the secant method.
            auto n0 = inc(eve::ceil( u_t(1.1)*az));
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
          auto n0  = eve::if_else(t, eve::ceil(e_t(1.1)*az), n);
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
    else
    {
      return cayley_extend_rev(cyl_bessel_jn, nn, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j0>, Z z) noexcept
  {
    return sinc(z);
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto rz = rec(z);
      return if_else(kyosu::abs(z) < eve::eps(eve::as(real(z)))
                    , eve::zero(eve::as(real(z)))
                    , (sinc(z)-cos(z))*rz
                    );
    }
    else
    {
      return cayley_extend(sph_bessel_j0, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_jn>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using u_t = eve::underlying_type_t<Z>;
      auto bd = [z](int n){
        auto st = eve::abs(eve::sin(eve::abs(arg(z))));
        auto r  = kyosu::abs(z);
        auto m = eve::maximum(eve::ceil((1.83+4.1*eve::pow(st, 0.33))*eve::pow(r, (0.91-0.43*eve::pow(st, 0.36)))+9*(1-eve::sqrt(st))));
        return eve::max(n+1, int(m));
      };

      auto j0 = kyosu::sph_bessel_j0(z);
      if (n == 0) return j0;
      auto j1 = kyosu::sph_bessel_j1(z);
      if (n == 1) return j1;

      auto rz = kyosu::rec(z);
      auto nn = bd(n);
      std::vector < Z > jj(nn+1);
      jj[nn] =  kyosu::complex(u_t(0));
      jj[nn-1] =  eve::sqrtsmallestposval(eve::as<u_t>()); //kyosu::complex(u_t(1));
      auto jnext =  kyosu::complex(u_t(0));
      auto j     =   kyosu::complex(eve::sqrtsmallestposval(eve::as<u_t>()));//kyosu::complex(u_t(1));
      auto init = j;
      auto jcur = jnext;
      auto res = j;
      for(int i=nn-1; i > 0 ; --i)
      {
        jcur = (2*i+1)*rz*j-jnext;
        if(i == n) res = j;
        jnext = j;
        j = jcur;
      }
      auto j0ltj1 = kyosu::abs(j0) <= kyosu::abs(j1);
      auto scalej0 = (j0/jcur);
      auto scalej1 = (j1/jnext);
      return res*if_else(j0ltj1, scalej0, scalej1);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_jn, n, z);
    }
  }

}
