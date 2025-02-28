//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <iostream>

namespace kyosu::_
{
  auto hyp_ps_infinity (auto a, auto b, auto c, auto z, auto notdone) noexcept
  {
    //std::cout<< std::endl << "hyp_ps_infinity" << std::endl;
    //std::cout << "z " << z << std::endl;
    //std::cout << "a " << a << std::endl;
    //std::cout << "b " << b << std::endl;
    //std::cout << "c " << c << std::endl;
    //std::cout << "notdone " << notdone << std::endl<< std::endl;

    using r_t = decltype(a+b+c+z);
    using u_t = eve::underlying_type_t<r_t>;
    if constexpr(eve::scalar_value<r_t>)
    {
      const int m = eve::nearest (real (b - a));
      const int phase = eve::sign_alternate(m);
      const int m_m1 = m - 1;
      const int m_p1 = m + 1;
      const r_t eps = b - a - m;
      const r_t a_mc_p1 = 1.0 - c + a;
      const r_t one_meps = 1.0 - eps;
      const r_t one_meps_mm = one_meps - m;
      const r_t a_pm = a + m;
      const r_t a_mc_p1_pm = a_mc_p1 + m;
      const r_t cma = c - a;
      const r_t eps_pa = eps + a;
      const r_t eps_pm_p1 =  eps + m + 1;
      const r_t eps_pa_mc_p1_pm = eps + a_mc_p1_pm;
      const r_t Pi_eps = M_PI*eps;
      const r_t eps_pa_pm = eps_pa + m;
      const r_t Gamma_c = 1.0/kyosu::tgamma_inv (c);
      const r_t Gamma_inv_eps_pa_pm = kyosu::tgamma_inv (eps_pa_pm);
      const r_t Gamma_inv_cma = kyosu::tgamma_inv (cma);
      const r_t z_inv = 1.0/z;
      const r_t pow_mz_ma = pow (-z,-a);
      const r_t Gamma_inv_one_meps = kyosu::tgamma_inv(one_meps);
      const r_t Gamma_prod = Gamma_c*Gamma_inv_cma*Gamma_inv_eps_pa_pm;

      const r_t A_first_term = (m > 0) ? (Gamma_prod*A_sum_init (m,eps,Gamma_inv_one_meps)) : (0.0);
      r_t A_sum = A_first_term;
      r_t A_term = A_first_term;

      if (kyosu::is_not_finite (A_first_term))
      {
        A_sum = A_term = kyosu::exp (kyosu::log_gamma (c) - kyosu::log_gamma (cma) - kyosu::log_gamma (b) + log_A_sum_init (m,eps));
        if ((imag (a) == 0.0) && (imag (b) == 0.0) && (imag (c) == 0.0)) A_sum = A_term = real (A_term);
      }

      const r_t pow_z_inv_m = kyosu::pow (z_inv,m);
      r_t B_first_term = B_sum_init_ps_infinity (a,c,Gamma_c,Gamma_inv_cma,Gamma_inv_one_meps,Gamma_inv_eps_pa_pm,z,m,eps,kyosu::true_(eve::as<r_t>()));
      //std::cout <<  "B_first_term " <<  B_first_term << std::endl;
      B_first_term *= pow_z_inv_m;

      r_t prod_B = pow_z_inv_m;
      for (int n = 0 ; n < m_m1 ; n++)
      {
        const r_t ratio = (a + n)*(a_mc_p1 + n)/(n + 1.0);
        A_term *= z_inv*ratio/(n + one_meps_mm);
        A_sum += A_term;
        prod_B *= ratio;
      }

      if (m > 0) prod_B *= (a + m - 1.0)*(a_mc_p1 + m - 1.0)/m;

      r_t B_extra_term = prod_B*Gamma_prod*Gamma_inv_one_meps;
      r_t B_term = B_first_term;
      r_t B_sum = B_first_term;
      const u_t B_prec = eve::eps(eve::as<u_t>())*kyosu::linfnorm (B_first_term);

      auto cv_poly1_der_tab = dcv_poly_calc(a,a_mc_p1,one_meps_mm,z_inv);
      auto cv_poly2_der_tab = dcv_poly_calc(b,eps_pa_mc_p1_pm,eps_pm_p1,z_inv);

      const int min_n = std::max (min_n_calc (cv_poly1_der_tab),min_n_calc (cv_poly2_der_tab));
      bool possible_false_cv = true;

      int n = 0;
      while (possible_false_cv || (kyosu::linfnorm (B_term) > B_prec))
      {
        const int n_pm_p1 = n + m_p1,n_p1 = n + 1;
        const r_t a_pm_pn = a_pm + n;
        const r_t a_mc_p1_pm_pn = a_mc_p1_pm + n;
        const r_t eps_pm_p1_pn = eps_pm_p1 + n;
        const r_t n_p1_meps = one_meps + n;
        const r_t eps_pa_pm_pn = eps_pa_pm + n;
        const r_t eps_pa_mc_p1_pm_pn = eps_pa_mc_p1_pm + n;
        const r_t prod1 = eps_pa_pm_pn*eps_pa_mc_p1_pm_pn;
        const r_t prod2 = eps_pm_p1_pn*n_p1,prod3 = a_pm_pn*a_mc_p1_pm_pn;
        B_term = z_inv*(B_term*prod1/prod2 + B_extra_term*(prod3/n_pm_p1 - a_pm_pn - a_mc_p1_pm_pn - eps + prod1/n_p1)/(eps_pm_p1_pn*n_p1_meps));
        //std::cout << "B_term " << B_term << std::endl;
        B_sum += B_term;
        B_extra_term *= z_inv*prod3/(n_pm_p1*n_p1_meps);
        if (possible_false_cv && (n >= min_n)) possible_false_cv = (dcv_calc (cv_poly1_der_tab, u_t(n)) > 0) || (dcv_calc (cv_poly2_der_tab, u_t(n)) > 0);
        n++;
      }
      //std::cout << "kyosu::is_eqz(eps))" << kyosu::is_eqz(eps) << std::endl;
      //std::cout << "A_sum " << A_sum << std::endl;
      //std::cout << "B_sum " << B_sum << std::endl;
      return (kyosu::is_eqz(eps)) ? (phase*pow_mz_ma*(A_sum + B_sum)) : ((A_sum + B_sum)*phase*pow_mz_ma*Pi_eps/kyosu::sinpi(eps));
    }
    else
    {
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
}
