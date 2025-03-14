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
  auto hyp_ps_infinity (auto a, auto b, auto c, auto z, auto notdone) noexcept
  {
    using r_t = decltype(a+b+c+z);
    using u_t = eve::underlying_type_t<r_t>;

    auto tol = eve::eps(as<u_t>());

    auto m = eve::nearest(real(b - a));
    r_t  phase(eve::sign_alternate(m));
    auto  m_m1 = dec(m);
    auto  m_p1 = inc(m);

    r_t eps = b - a - m;
    r_t a_mc_p1 = kyosu::inc(a-c);
    r_t one_meps = kyosu::oneminus(eps);
    r_t one_meps_mm = one_meps - m;
    r_t a_pm = a + m;
    r_t a_mc_p1_pm = a_mc_p1 + m;
    r_t cma = c - a;
    r_t eps_pa = eps + a;
    r_t  eps_pm_p1 =  kyosu::inc(eps + m);
    r_t eps_pa_mc_p1_pm = eps + a_mc_p1_pm;
    r_t pi_eps = eve::pi(eve::as<u_t>())*eps;
    r_t eps_pa_pm = eps_pa + m;
    r_t eps_pm = eps + m;
    r_t gamma_c = kyosu::tgamma(c);
    r_t gamma_inv_eps_pa_pm = kyosu::tgamma_inv(eps_pa_pm);
    r_t gamma_inv_cma = kyosu::tgamma_inv (cma);
    r_t z_inv = kyosu::rec(z);
    r_t pow_mz_ma = kyosu::pow(-z,-a);
    r_t gamma_inv_one_meps = kyosu::tgamma_inv(one_meps);
    r_t gamma_prod = gamma_c*gamma_inv_cma*gamma_inv_eps_pa_pm;

    r_t A_first_term = if_else(eve::is_gtz(m), gamma_prod*A_sum_init(m,eps,gamma_inv_one_meps), zero);
    r_t A_sum = A_first_term;
    r_t A_term = A_first_term;
    auto invalid_A_first_term = kyosu::is_not_finite(A_first_term);
    if(eve::any(invalid_A_first_term))
    {
      A_term = if_else(invalid_A_first_term
                      , kyosu::exp(kyosu::log_gamma(c) - kyosu::log_gamma(cma) - kyosu::log_gamma(b) + log_A_sum_init(m,eps))
                      , A_term);
      imag(A_term) = if_else(kyosu::is_real(a) && kyosu::is_real(b) && kyosu::is_real(c), zero, imag(A_term));
      A_sum = A_term;
    }


    auto pow_z_inv_m = kyosu::pow (z_inv,m);
    auto B_first_term = B_sum_init_ps_infinity(a,c,gamma_c,gamma_inv_cma,gamma_inv_one_meps,gamma_inv_eps_pa_pm,z,m,eps, notdone);

    B_first_term*= pow_z_inv_m;
    auto prod_B = pow_z_inv_m;
    auto mm_m1 = eve::maximum(m_m1);
    for (int n = 0 ; n < mm_m1 ; ++n)
    {
      auto ratio = (a + n)*(a_mc_p1 + n)/inc(n);
      A_term *= if_else(n < m_m1, z_inv*ratio/(n + one_meps_mm), zero);
      A_sum += A_term;
      prod_B *= kyosu::if_else(n < m_m1, ratio, one);
    }

    prod_B *= if_else(eve::is_gtz(m), dec(a+m)*dec(a_mc_p1+m)/m, one);

    auto B_extra_term = prod_B*gamma_prod*gamma_inv_one_meps;
    auto B_term = B_first_term;
    auto B_sum = B_first_term;
    auto B_prec = tol*kyosu::linfnorm(B_first_term);

    auto cv_poly1_der_tab = dcv_poly_calc(a,a_mc_p1,one_meps_mm,z_inv);
    auto cv_poly2_der_tab = dcv_poly_calc(b,eps_pa_mc_p1_pm,eps_pm_p1,z_inv);

    auto min_n = eve::max(min_n_calc(cv_poly1_der_tab), min_n_calc(cv_poly2_der_tab));
    auto possible_false_cv = kyosu::false_(kyosu::as<r_t>());
    auto maxit = 500;

    for(int n = 0;  n < maxit; ++n)
    {
      auto n_pm_p1 = n + m_p1;;
      auto n_p1 = inc(n);
      auto a_pm_pn = a_pm + n;
      auto a_mc_p1_pm_pn = a_mc_p1_pm + n;
      auto eps_pm_p1_pn = eps_pm_p1 + n;
      auto n_p1_meps = one_meps + n;
      auto eps_pa_pm_pn = eps_pa_pm + n;
      auto eps_pa_mc_p1_pm_pn = eps_pa_mc_p1_pm + n;
      auto eps_pm_pn = eps_pm + n;
      auto prod1 = eps_pa_pm_pn*eps_pa_mc_p1_pm_pn;
      auto prod2 = eps_pm_p1_pn*n_p1;
      auto prod3 = a_pm_pn*a_mc_p1_pm_pn;
      z_inv = z_inv+ kyosu::i(eve::as(z_inv))*2.4723e-310;//////////////
      B_term = z_inv*(B_term*prod1/prod2 + B_extra_term*(prod3/n_pm_p1 - a_pm_pn - a_mc_p1_pm_pn - eps + prod1/n_p1)/(eps_pm_p1_pn*n_p1_meps));
      B_sum += B_term;
      B_extra_term *= z_inv*prod3/(n_pm_p1*n_p1_meps);
      if (eve::all(!possible_false_cv &&  (kyosu::linfnorm (B_term) <= B_prec))) break;
      possible_false_cv = kyosu::if_else(possible_false_cv && (n >= min_n)
                                        , eve::is_gtz(dcv_calc(cv_poly1_der_tab,u_t(n))) || eve::is_gtz(dcv_calc (cv_poly2_der_tab,u_t(n)))
                                        , possible_false_cv);
    }
    return if_else(kyosu::is_eqz(eps)
                  , (phase*pow_mz_ma*(A_sum + B_sum))
                  , (A_sum + B_sum)*phase*pow_mz_ma*pi_eps/sinpi(eps)
                  );
  }
}
