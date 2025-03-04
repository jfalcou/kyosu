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
  auto hyp_ps_one(auto a, auto b, auto c, auto one_minus_z)
  {
    using r_t = decltype(a+b+c+one_minus_z);
    using u_t = eve::underlying_type_t<r_t>;

    auto tol = eve::eps(as<u_t>());
    auto m = eve::nearest(real(c - a - b));
    r_t  phase(eve::sign_alternate(m));
    auto  m_m1 = kyosu::dec(m);
    auto  m_p1 = kyosu::inc(m);
    r_t eps = c - a - b - m;
    r_t eps_pm(eps + m);
    r_t eps_pm_p1 = kyosu::inc(eps_pm);
    r_t a_pm(a + m);
    r_t b_pm(b + m);
    r_t one_meps(kyosu::oneminus(eps));
    r_t one_meps_mm = one_meps - m;
    r_t eps_pa = a + eps;
    r_t eps_pb = b + eps;
    r_t eps_pa_pm = eps_pa + m;
    r_t eps_pb_pm = eps_pb + m;
    r_t pi_eps = eve::pi(eve::as<u_t>())*eps;
    r_t gamma_c(kyosu::_::tgamma_impl(c));
    r_t gamma_inv_eps_pa_pm = kyosu::tgamma_inv (eps_pa_pm);
    r_t gamma_inv_eps_pb_pm = kyosu::tgamma_inv (eps_pb_pm);
    r_t gamma_prod = gamma_c*gamma_inv_eps_pa_pm*gamma_inv_eps_pb_pm;
    r_t gamma_inv_one_meps = kyosu::tgamma_inv(one_meps);

    r_t A_first_term = kyosu::if_else(eve::is_gtz(m),  (gamma_prod*A_sum_init (m,eps,gamma_inv_one_meps)), zero);
    r_t A_sum = A_first_term;
    r_t A_term = A_first_term;
    auto invalid_A_first_term = kyosu::is_not_finite(A_first_term);
    if(eve::any(invalid_A_first_term))
    {
      A_term =  kyosu::if_else(invalid_A_first_term
                              , kyosu::exp(kyosu::log_gamma(c) - kyosu::log_gamma(eps_pa_pm) - kyosu::log_gamma(eps_pb_pm) + log_A_sum_init(m,eps))
                              , A_term);
      if constexpr(!kyosu::concepts::real<r_t>)
        imag(A_term) = kyosu::if_else(kyosu::is_real(a) && kyosu::is_real(b) && kyosu::is_real(c), zero, imag(A_term));
      A_sum = A_term;
    }

    r_t pow_mzp1_m = kyosu::pow(one_minus_z,m);
    r_t B_first_term(B_sum_init_ps_one(a,b,c,gamma_c,gamma_inv_one_meps,gamma_inv_eps_pa_pm,gamma_inv_eps_pb_pm,one_minus_z,m,eps, kyosu::true_(eve::as<r_t>()))*pow_mzp1_m);

    r_t prod_B = pow_mzp1_m;
    auto mm_m1 = eve::maximum(m_m1);
    for (int n = 0 ; n < mm_m1 ; ++n)
    {
      auto ratio = (a+n)*(b+n)/eve::inc(n);
      A_term *= kyosu::if_else(n < m_m1, one_minus_z*ratio/(n + one_meps_mm), zero);
      A_sum += A_term;
      prod_B *= kyosu::if_else(n < m_m1, ratio, one);
    }
    prod_B *= kyosu::if_else(eve::is_gtz(m), dec(a+m)*dec(b+m)/m, one);

    r_t B_extra_term = prod_B*gamma_prod*gamma_inv_one_meps;
    r_t B_term = B_first_term;
    r_t B_sum = B_first_term;
    auto B_prec = tol*kyosu::linfnorm(B_first_term);

    auto cv_poly1_der_tab = dcv_poly_calc(a,b,one_meps_mm,              one_minus_z);
    auto cv_poly2_der_tab = dcv_poly_calc(eps_pb_pm,eps_pa_pm,eps_pm_p1,one_minus_z);

    auto min_n = eve::max(min_n_calc(cv_poly1_der_tab),min_n_calc(cv_poly2_der_tab));
    auto possible_false_cv = kyosu::false_(kyosu::as<r_t>());
    auto maxit = 500;

    for(int n = 0;  n < maxit; ++n)
    {
      auto n_pm_p1 = n + m_p1;
      auto n_p1 = eve::inc(n);
      auto a_pm_pn = a_pm + n;
      auto b_pm_pn = b_pm + n;
      auto eps_pm_p1_pn = eps_pm_p1 + n;
      auto n_p1_meps = one_meps + n;
      auto eps_pa_pm_pn = eps_pa_pm + n;
      auto eps_pb_pm_pn = eps_pb_pm + n;
      auto prod1 = eps_pa_pm_pn*eps_pb_pm_pn;
      auto prod2 = eps_pm_p1_pn*n_p1;
      auto prod3 = a_pm_pn*b_pm_pn;

      B_term = one_minus_z*(B_term*prod1/prod2 + B_extra_term*(prod3/n_pm_p1 - a_pm_pn - b_pm_pn - eps + prod1/n_p1)/(eps_pm_p1_pn*n_p1_meps));
      B_sum += B_term;
      B_extra_term *= one_minus_z*prod3/(n_pm_p1*n_p1_meps);
      if (eve::all(!possible_false_cv &&  (kyosu::linfnorm (B_term) <= B_prec))) break;
      possible_false_cv = kyosu::if_else(possible_false_cv && (n >= min_n)
                                        , eve::is_gtz(dcv_calc(cv_poly1_der_tab,u_t(n))) || eve::is_gtz(dcv_calc (cv_poly2_der_tab,u_t(n)))
                                        , possible_false_cv);
    }
    auto pAB_sum = (A_sum + B_sum)*phase;
    auto r = kyosu::if_else(kyosu::is_eqz(eps)
                           , pAB_sum
                           , pAB_sum*pi_eps/kyosu::sinpi(eps));
    return r;
  }
}
