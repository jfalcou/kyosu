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

  auto B_sum_init_ps_infinity (auto a, auto c, auto gamma_c, auto gamma_inv_cma,
                               auto gamma_inv_one_meps, auto gamma_inv_eps_pa_pm, auto z, auto m,
                               auto eps, auto notdone) noexcept
  {

    using r_t = decltype(a+c+z+gamma_c+gamma_inv_cma+gamma_inv_one_meps+gamma_inv_eps_pa_pm+m+eps);
    using u_t = eve::underlying_type_t<r_t>;

    const u_t pi = eve::pi(eve::as<u_t>());
    const auto inf_norm_eps = kyosu::linfnorm(eps);

    if constexpr(eve::scalar_value<r_t>)
    {
      const u_t phase = eve::sign_alternate(m);
      const r_t cma = c - a,a_mc_p1 = 1.0 - c + a;
      const r_t cma_meps = cma - eps;
      const r_t eps_pa_mc_p1 = eps + a_mc_p1;
      const r_t a_pm = a + m;
      const r_t gamma_inv_cma_meps = kyosu::tgamma_inv (cma_meps);
      const r_t one_meps = 1.0 - eps;
      const r_t pi_eps_pm = pi*(eps + m);

      r_t gamma_inv_one_meps_mm = gamma_inv_one_meps;
      for (int i = 1 ; i <= m ; ++i) gamma_inv_one_meps_mm *= one_meps - i;

      if (inf_norm_eps > u_t(0.1))
      {

        const r_t gamma_inv_eps_pm_p1 = phase*kyosu::sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
        r_t prod1 = gamma_inv_cma*gamma_inv_eps_pa_pm*gamma_inv_one_meps;
        r_t prod2 = kyosu::tgamma_inv (a)*gamma_inv_cma_meps*gamma_inv_eps_pm_p1*pow (-z,-eps);

        for (int n = 0 ; n < m ; n++)
        {
          const u_t n_p1 = eve::inc(n);
          const r_t a_pn = a + n,a_mc_p1_pn = a_mc_p1 + n,eps_pa_mc_p1_pn = eps_pa_mc_p1 + n;
          prod1 *= a_pn*a_mc_p1_pn/n_p1, prod2 *= eps_pa_mc_p1_pn;
        }

        const r_t res = gamma_c*(prod1 - prod2)/eps;
       return res;
      }
      else
      {
        const int n0 = -eve::nearest(real(a_mc_p1));
        const auto is_eps_non_zero = (one_meps-m != oneminus(m));
        const auto is_n0_here = (n0 >= 0) && (n0 < m);

        u_t gamma_inv_mp1 = u_t(1.0);
        r_t prod_a = 1.0;
        r_t prod_a_mc_p1 = 1.0;
        r_t prod_eps_pa_mc_p1_n0 = (is_n0_here) ? (1.0) : (0.0);
        r_t prod_eps_pa_mc_p1 = r_t(1);
        r_t sum(0);
        for (int n = 0 ; n < m ; n++)
        {
          const r_t a_pn = a + n;
          const r_t a_mc_p1_pn = a_mc_p1 + n;
          const r_t eps_pa_mc_p1_pn = eps_pa_mc_p1 + n;
          prod_a *= a_pn, prod_a_mc_p1 *= a_mc_p1_pn;
          prod_eps_pa_mc_p1 *= eps_pa_mc_p1_pn;
          gamma_inv_mp1 /= inc(n);

          if (n != n0)
          {
            if (is_n0_here) prod_eps_pa_mc_p1_n0 *= eps_pa_mc_p1_pn;
            sum += (is_eps_non_zero) ? (kyosu::log1p (eps/a_mc_p1_pn)) : kyosu::rec(a_mc_p1_pn);
          }
        }
        const r_t gamma_inv_eps_pm_p1 = (is_eps_non_zero) ? (phase*kyosu::sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm)) : (gamma_inv_mp1);
        const r_t sum_term = (is_eps_non_zero) ? (expm1 (sum)/eps) : (sum),prod_diff_eps = prod_eps_pa_mc_p1_n0 + prod_a_mc_p1*sum_term;

        auto mlogmz = -kyosu::log(-z);
        const r_t z_term = (is_eps_non_zero) ? kyosu::expm1(eps*mlogmz/eps) : mlogmz;
        const r_t gamma_inv_a_pm = kyosu::tgamma_inv (a_pm),gamma_prod1 = gamma_inv_cma*gamma_inv_eps_pa_pm;
        const r_t prod1 = gamma_prod1*gamma_inv_mp1*(gamma_inv_diff_eps (r_t(1),-eps,kyosu::true_(eve::as<r_t>()))*prod_eps_pa_mc_p1 - gamma_inv_one_meps*prod_diff_eps);
        const r_t prod_2a = gamma_prod1*gamma_inv_diff_eps (r_t(eve::inc(m)),eps,kyosu::true_(eve::as<r_t>()));
        const r_t prod_2b = gamma_inv_cma*gamma_inv_eps_pm_p1*gamma_inv_diff_eps (a_pm,eps,kyosu::true_(eve::as<r_t>()));
        auto gide = gamma_inv_diff_eps(cma,-eps,kyosu::true_(eve::as<r_t>()));
        auto gg = gamma_inv_eps_pm_p1*gamma_inv_a_pm;
        auto gz = gamma_inv_cma_meps*z_term;
        const r_t prod_2c = gamma_inv_eps_pm_p1*gamma_inv_a_pm*(gamma_inv_diff_eps (cma,-eps,kyosu::true_(eve::as<r_t>())) + gamma_inv_cma_meps*z_term);


        const r_t prod2 = prod_eps_pa_mc_p1*(prod_2a - prod_2b - prod_2c);
        auto  res = gamma_c*prod_a*(prod1 + prod2);


        if (kyosu::is_finite (res))
          return res;
        else
        {
          const r_t gamma_inv_eps_pm_p1 = phase*kyosu::sin(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
          r_t prod1 = gamma_inv_cma*gamma_inv_eps_pa_pm*gamma_inv_one_meps,prod2 = kyosu::tgamma_inv (a)*gamma_inv_cma_meps*gamma_inv_eps_pm_p1*pow (-z,-eps);

          for (int n = 0 ; n < m ; n++)
          {
            const u_t n_p1 = inc(n);
            const r_t a_pn = a + n,a_mc_p1_pn = a_mc_p1 + n;
            const r_t eps_pa_mc_p1_pn = eps_pa_mc_p1 + n;
            prod1 *= a_pn*a_mc_p1_pn/n_p1;
            prod2 *= eps_pa_mc_p1_pn;
          }

          const r_t res_default = gamma_c*(prod1 - prod2)/eps;
          return res_default;
        }
      }
    }
    else
    {

      const r_t phase(eve::sign_alternate(m));
      r_t cma(c - a);
      r_t a_mc_p1(inc(a-c));
      r_t cma_meps(cma - eps);
      r_t eps_pa_mc_p1(eps + a_mc_p1);
      r_t a_pm(a + m);
      r_t gamma_inv_cma_meps(kyosu::tgamma_inv (cma_meps));
      r_t one_meps(kyosu::oneminus(eps));
      r_t pi_eps_pm(eve::pi(as<u_t>())*(eps + m));

      r_t gamma_inv_one_meps_mm = gamma_inv_one_meps;
      auto mm =  eve::maximum(m);
      for (int i = 1 ; i <= mm ; ++i) gamma_inv_one_meps_mm *= if_else(i <= m, one_meps - i, one);

      auto br_eps_gt =  [&](){//if (inf_norm_eps > 0.1)


         auto gamma_inv_eps_pm_p1 = phase*sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
        auto prod1 = gamma_inv_cma*gamma_inv_eps_pa_pm*gamma_inv_one_meps;
        auto prod2 = kyosu::tgamma_inv(a)*gamma_inv_cma_meps*gamma_inv_eps_pm_p1*kyosu::pow (-r_t(z),-r_t(eps));
        for (int n = 0 ; n < mm ; ++n)
        {
          const double n_p1 = inc(n);
          auto a_pn = a + n;
          auto a_mc_p1_pn = a_mc_p1 + n;
          auto eps_pa_mc_p1_pn = eps_pa_mc_p1 + n;
          auto test = n < m;
          prod1 *= if_else(test, a_pn*a_mc_p1_pn/n_p1, one);
          prod2 *= if_else(test, eps_pa_mc_p1_pn, one);
        }
        auto res = gamma_c*(prod1 - prod2)/eps;
        return res;
      };

      auto br_eps_le =  [&](){//if (inf_norm_eps <=  0.1)

        auto n0 = -eve::nearest(real(a_mc_p1));
        auto is_eps_non_zero = (one_meps-m != oneminus(m));
        auto is_n0_here = eve::is_gez(n0) && (n0 < m);

        auto  gamma_inv_mp1 =  kyosu::one(as<r_t>());
        auto prod_a =  kyosu::one(as<r_t>());
        auto prod_a_mc_p1 =  kyosu::one(as<r_t>());
        auto prod_eps_pa_mc_p1_n0 = if_else(is_n0_here, r_t(1), zero);
        auto prod_eps_pa_mc_p1 = kyosu::one(as<r_t>());
        auto sum = kyosu::zero(as<r_t>());

        for (int n = 0 ; n < mm ; ++n)
        {
          auto a_pn = a + n;
          auto a_mc_p1_pn = a_mc_p1 + n;
          auto eps_pa_mc_p1_pn = eps_pa_mc_p1 + n;
          auto testnm = n < m;
          prod_a *= if_else(testnm, a_pn, one);
          prod_a_mc_p1 *= if_else(testnm, a_mc_p1_pn, one);
          prod_eps_pa_mc_p1 *= if_else(testnm, eps_pa_mc_p1_pn, one);
          gamma_inv_mp1 /= if_else(testnm,u_t(inc(n)), one);
          auto ndiffn0 = n != n0;
          if (eve::any(ndiffn0))
          {
            prod_eps_pa_mc_p1_n0 *= if_else(is_n0_here && testnm && ndiffn0, eps_pa_mc_p1_pn, one);
            sum += if_else(is_eps_non_zero && testnm, (log1p (eps/a_mc_p1_pn)),  (1.0/a_mc_p1_pn));
          }
        }


        auto gamma_inv_eps_pm_p1 = if_else(is_eps_non_zero, (phase*kyosu::sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm)), gamma_inv_mp1);
        auto sum_term = if_else(is_eps_non_zero, kyosu::expm1(sum)/eps, sum);
        auto prod_diff_eps = prod_eps_pa_mc_p1_n0 + prod_a_mc_p1*sum_term;

        auto mlogmz = -kyosu::log(-z);
        auto z_term = if_else(is_eps_non_zero, kyosu::expm1(eps*mlogmz)/eps, mlogmz);
        auto gamma_inv_a_pm = kyosu::tgamma_inv (a_pm);
        auto gamma_prod1 = gamma_inv_cma*gamma_inv_eps_pa_pm;

        auto prod1 = gamma_prod1*gamma_inv_mp1*(gamma_inv_diff_eps(kyosu::one(as<r_t>()), eps, notdone)*prod_eps_pa_mc_p1 - gamma_inv_one_meps*prod_diff_eps);
        auto prod_2a = gamma_prod1*gamma_inv_diff_eps(inc(m),eps, notdone);
        auto prod_2b = gamma_inv_cma*gamma_inv_eps_pm_p1*gamma_inv_diff_eps (a_pm,eps, notdone);
        auto gide = gamma_inv_diff_eps(cma,-eps, notdone);
         auto gg = gamma_inv_eps_pm_p1*gamma_inv_a_pm;
        auto gz = gamma_inv_cma_meps*z_term;
        auto prod_2c = gamma_inv_eps_pm_p1*gamma_inv_a_pm*(gamma_inv_diff_eps(cma,-eps, notdone) + gamma_inv_cma_meps*z_term);



         auto prod2 = prod_eps_pa_mc_p1*(prod_2a - prod_2b - prod_2c);
         auto res = gamma_c*prod_a*(prod1 + prod2);


        auto finite = kyosu::is_finite (res);
        if (eve::all(finite))
        {
          if constexpr(kyosu::concepts::real<r_t>)
            return real(res);
          else
            return res;
        }
        else
        {
          auto gamma_inv_eps_pm_p1 = phase*sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
          auto prod1 = gamma_inv_cma*gamma_inv_eps_pa_pm*gamma_inv_one_meps;
          auto prod2 = kyosu::tgamma_inv (a)*gamma_inv_cma_meps*gamma_inv_eps_pm_p1*kyosu::pow(-z,-eps);

          for (int n = 0 ; n < mm ; n++)
          {
            const double n_p1 = inc(n);
            auto a_pn = a + n;
            auto a_mc_p1_pn = a_mc_p1 + n;
            auto eps_pa_mc_p1_pn = eps_pa_mc_p1 + n;
            prod1 *= kyosu::if_else(n < m, a_pn*a_mc_p1_pn/n_p1, one);
            prod2 *= kyosu::if_else(n < m, eps_pa_mc_p1_pn, one);
          }

          auto res_default = gamma_c*(prod1 - prod2)/eps;
          return if_else(finite, res, res_default);
        }
      };

      auto r = kyosu::nan(as<r_t>());
      if( eve::any(notdone) )
      {
        auto gt = inf_norm_eps > u_t(0.1);
        notdone = next_interval(br_eps_gt, notdone, gt, r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_eps_le, notdone, !gt, r);
        }
      }
      return r;
    }
  }
}
