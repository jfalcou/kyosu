//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/functions/is_not_equal.hpp>>
#include <iostream>

namespace kyosu::_
{

  auto  gamma_ratio_diff_small_eps(auto z, auto eps, auto notdone) -> decltype(z+eps)
  {
       std::cout << "in gamma_ratio_diff_small_eps" << std::endl;
    using r_t = decltype(z+eps);
    using u_t = eve::underlying_type_t<r_t>;
    constexpr u_t g = 4.7421875;
    constexpr u_t hf = eve::half(eve::as<u_t>());
    // |eps| must be less than 0.1
    EVE_ASSERT(eve::all(kyosu::abs(eps) < 0.1), "One must have |eps| < 0.1");
    constexpr u_t c[15] = {0.99999999999999709182,
                           57.156235665862923517,
                           -59.597960355475491248,
                           14.136097974741747174,
                           -0.49191381609762019978,
                           0.33994649984811888699E-4,
                           0.46523628927048575665E-4,
                           -0.98374475304879564677E-4,
                           0.15808870322491248884E-3,
                           -0.21026444172410488319E-3,
                           0.21743961811521264320E-3,
                           -0.16431810653676389022E-3,
                           0.84418223983852743293E-4,
                           -0.26190838401581408670E-4,
                           0.36899182659531622704E-5};

    if constexpr(eve::scalar_value<r_t>)
    {
      const r_t nan   = kyosu::nan(kyosu::as<r_t>());
      const u_t zer = eve::zero(kyosu::as<u_t>());

      const u_t pi  = eve::pi(kyosu::as<u_t>());

      if (kyosu::linfnorm(eps) > u_t(0.1)) return kyosu::cinf(eve::as<r_t>());

      const r_t eps_pz = z + eps,z_m_0p5 = z - hf;
      const r_t z_pg_m0p5 = z_m_0p5 + g;
      const r_t eps_pz_pg_m0p5 = z_pg_m0p5 + eps;
      const r_t zm1 = dec(z);
      const r_t zm1_p_eps = zm1 + eps;
      const u_t x = real (z);
      const u_t eps_px = real (eps_pz);
      const int n = eve::nearest (x);
      const int m = eve::nearest (eps_px);

      if ((z == n) && (n <= 0)) return kyosu::cinf(eve::as<r_t>());
      if ((eps_pz == m) && (m <= 0)) return kyosu::cinf(eve::as<r_t>());


      if ((x >= hf) || (eps_px >= hf))
      {
        r_t sum_num = zer, sum_den = c[0];

        for (int i = 1 ; i < 15 ; ++i)
        {
          const r_t ci_zm1_pi_inv = c[i]/(zm1 + i);
          sum_num += ci_zm1_pi_inv/(zm1_p_eps + i), sum_den += ci_zm1_pi_inv;
        }

        if (eps != zer)
          return kyosu::expm1(z_m_0p5*kyosu::log1p(eps/z_pg_m0p5) + eps*kyosu::log(eps_pz_pg_m0p5) - eps + kyosu::log1p(-eps*sum_num/sum_den))/eps;
        else
          return z_m_0p5/z_pg_m0p5 + dec(kyosu::log(eps_pz_pg_m0p5)) - sum_num/sum_den;
      }
      else
      {
        if (kyosu::is_nez(eps))
        {
          const auto [s, c] = sinpicospi(eps);
          const r_t term = s*cotpi(z-n);
          const r_t T1_eps_z = (c + term)*gamma_ratio_diff_small_eps (1.0 - z,-eps, notdone);
          const r_t sin_Pi_2_eps = sinpi(hf*eps);
          const r_t T2_eps_z = (u_t(2.0)*sin_Pi_2_eps*sin_Pi_2_eps - term)/eps;
          const r_t T_eps_z = T1_eps_z + T2_eps_z;

          return (T_eps_z/(oneminus(eps*T_eps_z)));
        }
        else  return gamma_ratio_diff_small_eps(kyosu::oneminus(z),r_t(0), notdone) - pi*kyosu::cotpi(z-n);
      }
    }
    else // simd
    {
      auto eps_pz         = z + eps;
      auto z_m_0p5        = z - hf;
      auto z_pg_m0p5      = z_m_0p5 + g;
      auto eps_pz_pg_m0p5 = z_pg_m0p5 + eps;
      auto zm1            = kyosu::dec(z);
      auto zm1_p_eps      = zm1 + eps;

      auto x = real(z);
      auto eps_px = real(eps_pz);
      auto n = eve::nearest(x);
      [[maybe_unused]] auto m = eve::nearest(eps_px);
      auto zero_eps =  is_eqz(eps);


      auto br_0 = [&](auto test){
       std::cout << "in br_0" << std::endl;
        r_t  sum_num = kyosu::zero(kyosu::as<r_t>());
        r_t  sum_den(c[0]);
        for (int i = 1; i < 15; ++i)
        {
          auto ci_zm1_pi_inv = c[i]/(zm1 + i);
          sum_num += ci_zm1_pi_inv/(zm1_p_eps + i);
          sum_den += ci_zm1_pi_inv;
        }
        auto r =  kyosu::expm1(z_m_0p5*kyosu::log1p(eps/z_pg_m0p5) + eps*kyosu::log(eps_pz_pg_m0p5) - eps + kyosu::log1p(-eps*sum_num/sum_den))/eps;
        if (eve::none(zero_eps)) return r;
        else
        {
          if constexpr(kyosu::concepts::real<r_t>)
            return if_else(zero_eps
                          , (z_m_0p5/z_pg_m0p5 + eve::log(eps_pz_pg_m0p5) - eve::one(eve::as<u_t>()) - sum_num/sum_den)
                          , r);
          else
            return if_else(zero_eps
                          , (z_m_0p5/z_pg_m0p5 + kyosu::log(eps_pz_pg_m0p5) - eve::one(eve::as<u_t>()) - sum_num/sum_den)
                          , r);
        }
      };

      auto br_1 = [&](auto test, auto rr){
        std::cout << "in br_1" << notdone << std::endl;
        std::cout << "in br_1" << (notdone && !test) << std::endl;
        if (eve::none(notdone && !test)) return rr;
        auto [s, c]   = kyosu::sinpicospi(eps);
        auto term     = s*kyosu::cotpi(z-n);
        auto t1_eps_z = (c + term)*gamma_ratio_diff_small_eps(kyosu::oneminus(z),-eps, notdone && !test);
        auto s_eps_o2 = kyosu::sinpi(hf*eps);
        auto t2_eps_z = (2.0*sqr(s_eps_o2) - term)/eps;
        auto t_eps_z  = t1_eps_z + t2_eps_z;
        auto r        =  t_eps_z/kyosu::oneminus(eps*t_eps_z);
        if (eve::none(zero_eps) )
        {
          return r;
        }
        else
        {
          return if_else(zero_eps && notdone
                        , gamma_ratio_diff_small_eps(kyosu::oneminus(z),zero(as<r_t>()), notdone && !test) - eve::pi(eve::as<u_t>())*kyosu::cotpi(z-n)
                        , r
                        );
        }
      };

      auto r       = kyosu::cinf(kyosu::as<r_t>());
      auto test1(kyosu::is_not_equal(z, n) || eve::is_gtz(n)); // z is not negative integer
      auto test2(kyosu::is_not_equal(eps_pz, m) || eve::is_gtz(m)); //z+eps is not negative integer
      notdone = notdone || (test2 && test1);
      if( eve::any(notdone ) )
      {
        auto test = eve::is_greater_equal(x, hf) || eve::is_greater_equal(eps_px, hf);
        notdone = next_interval(br_0, notdone, test && notdone, r, test && notdone);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_1, notdone, !test && notdone, r, !test && notdone, r);
        }
      }
      return r;
    }
  }
}
