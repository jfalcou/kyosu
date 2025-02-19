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
  auto B_sum_init_ps_one (auto a, auto b, auto c,
           auto gamma_c, auto gamma_inv_one_meps,
           auto gamma_inv_eps_pa_pm, auto gamma_inv_eps_pb_pm,
           auto one_minus_z, auto m, auto eps, auto notdone) noexcept
  {
    using r_t = decltype(a+b+c+gamma_c+gamma_inv_one_meps+gamma_inv_eps_pa_pm+gamma_inv_eps_pb_pm+one_minus_z+eps+m);
    using u_t = eve::underlying_type_t<r_t>;

    const u_t pi = eve::pi(eve::as<u_t>());
    const auto inf_norm_eps = kyosu::linfnorm(eps);

    if constexpr(eve::scalar_value<r_t>)
    {
       const int phase = eve::sign_alternate(m);
      const r_t a_pm = a + m;
      const r_t b_pm = b + m;
      const r_t one_meps = kyosu::oneminus(eps);
      const r_t pi_eps_pm = pi*(eps + m);

      r_t gamma_inv_one_meps_mm = gamma_inv_one_meps;
      for (int i = 1 ; i <= m ; ++i) gamma_inv_one_meps_mm *= one_meps - i;

      if (inf_norm_eps > u_t(0.1))
      {

        const r_t gamma_inv_eps_pm_p1 = phase*kyosu::sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
        r_t prod1 = gamma_inv_one_meps*gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm;
        for (int n = 0 ; n < m ; n++) prod1 *= (a + n)*(b + n)/inc(n);
        const r_t prod2 = kyosu::tgamma_inv (a)*kyosu::tgamma_inv (b)*gamma_inv_eps_pm_p1*kyosu::pow (one_minus_z,eps);
        r_t res = gamma_c*(prod1 - prod2)/eps;
        return res;
      }
      else
      {
        u_t gamma_inv_mp1(1);
        r_t prod_ab = 1.0;
        for (int n = 0 ; n < m ; n++){ //replace with rising_factorial and gamma_inv ?
          gamma_inv_mp1 /= inc(n);
          prod_ab *= (a + n)*(b + n);
        }

        const auto is_eps_non_zero = (one_meps-m != eve::oneminus(m));
        const r_t gamma_inv_eps_pm_p1 = (is_eps_non_zero) ? (phase*kyosu::sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm)) : (gamma_inv_mp1);
        const r_t gamma_inv_a_pm = kyosu::tgamma_inv (a_pm),gamma_inv_b_pm = kyosu::tgamma_inv (b_pm);
        const r_t z_term = (is_eps_non_zero) ? (expm1 (eps*kyosu::log (one_minus_z))/eps) : (kyosu::log (one_minus_z));

        const r_t prod1 = gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm*(gamma_inv_mp1*gamma_inv_diff_eps (r_t(1),-eps, true) + gamma_inv_diff_eps (r_t(m+1),eps, true));
        const r_t prod2 = gamma_inv_eps_pm_p1*(gamma_inv_eps_pb_pm*gamma_inv_diff_eps (a_pm,eps, true) + gamma_inv_a_pm*gamma_inv_diff_eps (b_pm,eps, true));
        const r_t prod3 = gamma_inv_a_pm*gamma_inv_b_pm*gamma_inv_eps_pm_p1*z_term;

        const r_t res = gamma_c*prod_ab*(prod1 - prod2 - prod3);
        if (kyosu::is_finite (res))
          return res;
        else
        {
          const r_t gamma_inv_eps_pm_p1 = phase*kyosu::sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
          r_t prod1 = gamma_inv_one_meps*gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm;
          for (int n = 0 ; n < m ; n++) prod1 *= (a + n)*(b + n)/eve::inc(n);
          const r_t prod2 = kyosu::tgamma_inv (a)*kyosu::tgamma_inv (b)*gamma_inv_eps_pm_p1*pow (one_minus_z,eps);
          const r_t res_default = gamma_c*(prod1 - prod2)/eps;
          return res_default;
        }
      }
    }
    else
    {

      auto phase = eve::sign_alternate(m);
      r_t a_pm(a + m);
      r_t b_pm(b + m);
      r_t one_meps(oneminus(eps));
      r_t pi_eps_pm(pi*(eps + m));

      r_t gamma_inv_one_meps_mm = gamma_inv_one_meps;
      auto mm = eve::maximum(m);
      for (int i = 1 ; i <= mm ; i++) gamma_inv_one_meps_mm *= if_else(m <= mm, (one_meps - i), eve::one);

      auto br_gt = [&](){ //inf_norm_eps > 0.1
        auto gamma_inv_eps_pm_p1 = phase*sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);

        auto prod1 = gamma_inv_one_meps*gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm;
        for (int n = 0 ; n < mm ; ++n) prod1 *= if_else(m <= mm, (a+n)*(b+n)/inc(n), eve::one);
        auto pomz = [](auto zz, auto e){
          if constexpr(kyosu::concepts::real<r_t>) return eve::pow(zz,e);
          else                                     return kyosu::pow(zz,e);
        };
        auto pmz = pomz(one_minus_z,eps);
        auto prod2 = kyosu::tgamma_inv(a)*kyosu::tgamma_inv(b)*gamma_inv_eps_pm_p1*pmz;
        auto res = gamma_c*(prod1 - prod2)/eps;
        return res;
      };

      auto br_le = [&](){
        r_t gamma_inv_mp1(1);
        r_t prod_ab(1);

        for (int n = 0 ; n < mm ; ++n){
          auto test = n < m;
          gamma_inv_mp1 = gamma_inv_mp1/kyosu::if_else(test, r_t(kyosu::inc(n)), one);
          prod_ab *= kyosu::if_else(test, (a+n)*(b+n), one);
        }

        auto is_eps_non_zero = (one_meps-m != kyosu::oneminus(m));
        auto gamma_inv_eps_pm_p1 = if_else(is_eps_non_zero, (phase*sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm)),  (gamma_inv_mp1));
        auto gamma_inv_a_pm = kyosu::tgamma_inv(a_pm);
        auto gamma_inv_b_pm = kyosu::tgamma_inv (b_pm);
        auto log_one_minus_z = kyosu::log(one_minus_z);
        auto z_term = kyosu::if_else(is_eps_non_zero, (expm1(eps*log_one_minus_z)/eps), (log_one_minus_z));

        auto prod1 = gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm*(gamma_inv_mp1*gamma_inv_diff_eps(eve::one(eve::as<u_t>()), -eps, notdone) + gamma_inv_diff_eps (inc(m),eps, notdone));
        auto prod2 = gamma_inv_eps_pm_p1*(gamma_inv_eps_pb_pm*gamma_inv_diff_eps(a_pm,eps, notdone) + gamma_inv_a_pm*gamma_inv_diff_eps(b_pm,eps, notdone));
        auto prod3 = gamma_inv_a_pm*gamma_inv_b_pm*gamma_inv_eps_pm_p1*z_term;

        auto res = gamma_c*prod_ab*(prod1 - prod2 - prod3);
        auto finite = kyosu::is_finite (res);
        if (eve::all(finite))
        {
          return res;
        }
        else
        {
          auto gamma_inv_eps_pm_p1 = phase*sinpi(eps)/(pi_eps_pm*gamma_inv_one_meps_mm);
          auto prod1 = gamma_inv_one_meps*gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm;
          for (int n = 0 ; n < mm ; n++) prod1 *= if_else(n < m, (a + n)*(b + n)/inc(n), one);
          auto prod2 = kyosu::tgamma_inv (a)*kyosu::tgamma_inv(b)*gamma_inv_eps_pm_p1*kyosu::pow(one_minus_z,eps);
          auto res_default = gamma_c*(prod1 - prod2)/eps;
          return if_else(finite, res, res_default);
        }
      };

      auto r = kyosu::nan(as<r_t>());
//      auto notdone = is_nan(r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_gt, notdone, inf_norm_eps > u_t(0.1), r);
        if( eve::any(notdone) )
        {
          last_interval(br_le, notdone, r);
        }
      }
      return r;
    }
  }

  auto B_sum_init_ps_one (auto a, auto b, auto c,
           auto gamma_c, auto gamma_inv_one_meps,
           auto gamma_inv_eps_pa_pm, auto gamma_inv_eps_pb_pm,
           auto one_minus_z, auto m, auto eps) noexcept
  {
    using r_t = decltype(a+b+c+gamma_c+gamma_inv_one_meps+gamma_inv_eps_pa_pm+gamma_inv_eps_pb_pm+one_minus_z+eps+m);
    return B_sum_init_ps_one (a, b, c,
           gamma_c, gamma_inv_one_meps,
           gamma_inv_eps_pa_pm, gamma_inv_eps_pb_pm,
                              one_minus_z, m, eps, kyosu::true_(eve::as<r_t>()));
  }
}
