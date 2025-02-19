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
  auto hyp_ps_cp_rest(auto a, auto b, auto c, auto z, auto notdone) noexcept
  {
    using r_t = decltype(a+b+c+z);
    using u_t = eve::underlying_type_t<r_t>;

    if constexpr(eve::scalar_value<r_t>)
    {
      const auto abs_z = abs (z);
      const auto is_abs_z_small = abs_z < u_t(1);

      const r_t z0 = (is_abs_z_small) ? (u_t(0.9)*z/abs_z) : (u_t(1.1)*z/abs_z);
      const r_t zc = z - z0;
      const r_t zc_z0_ratio = zc/(z0*(1.0 - z0));
      const r_t z0_term1 = 2.0*z0 - 1.0;
      const r_t z0_term2 = c - kyosu::inc(a + b)*z0;

      const r_t hyp_ps_z0 = (is_abs_z_small) ? (hyp_ps_zero (a,b,c,z0)) : (hyp_ps_infinity (a,b,c,z0,kyosu::true_(eve::as<r_t>())));
      const r_t dhyp_ps_z0 = (is_abs_z_small) ? (hyp_ps_zero (kyosu::inc(a), kyosu::inc(b),kyosu::inc(c),z0)*a*b/c,kyosu::true_(eve::as<r_t>())) :
        (hyp_ps_infinity (kyosu::inc(a), kyosu::inc(b),kyosu::inc(c),z0,kyosu::true_(eve::as<r_t>()))*a*b/c);

      int n = 0;
      r_t an = hyp_ps_z0;
      r_t anp1 = zc*dhyp_ps_z0;
      r_t sum = an + anp1;

      const u_t prec = 1E-15*(kyosu::linfnorm (an) + kyosu::linfnorm (anp1));

      while (kyosu::linfnorm (an) + kyosu::linfnorm (anp1) > prec)
      {
        r_t anp2 = zc_z0_ratio*(anp1*(n*z0_term1 - z0_term2) + an*zc*(a + n)*(b + n)/eve::inc(n))/(n + 2);
        sum += anp2;
        n++;
        an = anp1;
        anp1 = anp2;
      }

      return sum;
    }
    else
    {
      auto abs_z = kyosu::abs (z);
      auto is_abs_z_small = abs_z < u_t(1);
      auto tol = eve::eps(as<u_t>());

      r_t z0 = kyosu::if_else(is_abs_z_small, u_t(0.9), u_t(1.1))*z/abs_z;
      r_t zc = z - z0;
      r_t zc_z0_ratio = zc/(z0*kyosu::oneminus(z0));
      r_t z0_term1 = kyosu::dec(z0+z0);
      r_t z0_term2 = c - kyosu::inc(a + b)*z0;
      r_t inca = kyosu::inc(a);
      r_t incb = kyosu::inc(b);
      r_t incc = kyosu::inc(c);
      r_t hyp_ps_z0  = kyosu::if_else(is_abs_z_small, hyp_ps_zero (a,b,c,z0, notdone),  hyp_ps_infinity (a,b,c,z0, notdone));
      r_t dhyp_ps_z0 = kyosu::if_else(is_abs_z_small
                                     , hyp_ps_zero (inca, incb, incc, z0)
                                     , hyp_ps_infinity (inca, incb, incc, z0, notdone)
                                     )*a*b/c;


      r_t an = hyp_ps_z0;
      r_t anp1 = zc*dhyp_ps_z0;
      r_t sum = an + anp1;

      auto prec = tol*(kyosu::linfnorm (an) + kyosu::linfnorm (anp1));

      auto maxit = 500;

      for(int n = 0;  n < maxit; ++n)
      {
        if (eve::all(kyosu::linfnorm(an) + kyosu::linfnorm(anp1) > prec)) break;
        r_t anp2 = zc_z0_ratio*(anp1*(n*z0_term1 - z0_term2) + an*zc*(a+n)*(b+n)/eve::inc(n))/(n + 2);
        sum += anp2;
        an = anp1;
        anp1 = anp2;
      }
      return sum;
    }
  }
}
