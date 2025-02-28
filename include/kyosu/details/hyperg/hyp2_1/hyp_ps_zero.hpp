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
  auto hyp_ps_zero(auto a, auto b, auto c, auto z, auto notdone)
  {
    constexpr int maxit = 512;
    using r_t = decltype(a+b+c+z);
    using u_t = eve::underlying_type_t<r_t>;

    if constexpr(eve::scalar_value<r_t>)
    {
      r_t term(1);
      r_t sum(1);
      const int na = eve::abs(eve::nearest (real(a)));
      const int nb = eve::abs(eve::nearest (real(b)));

      if (a == -na)
      {
        for (int n = 0 ; n < na ; n++)
        {
          term *= z*(a+n)*(b+n)/((n+1.0)*(c+n));
          sum += term;
        }
      }
      else if (b == -nb)
      {
        for (int n = 0 ; n < nb ; n++)
        {
          term *= z*(a+n)*(b+n)/((n+1.0)*(c+n));
          sum += term;
        }
      }
      else
      {
        auto  dcv_tab = dcv_poly_calc(a,b,c,z);
        const int min_n = min_n_calc (dcv_tab);
        bool possible_false_cv = true;
        int n = 0;
        int maxit = 512;
        while (possible_false_cv || (kyosu::linfnorm (term) > 1E-15))
        {
          term *= z*(a+n)*(b+n)/((n+1.0)*(c+n));
          sum += term;
          if (possible_false_cv && (n >= min_n)) possible_false_cv = (dcv_calc(dcv_tab,u_t(n)) > 0);
          n++;
          if (n > maxit) return kyosu::cinf(as<r_t>());
        }
      }
      return sum;
    }
    else
    {
      auto  na = eve::abs(eve::nearest(real(a)));
      auto  nb = eve::abs(eve::nearest(real(b)));
      auto  ta = a == -na;
      auto  tb = b == -nb;
      auto  tab = ta && tb;
      auto less_nanb = eve::is_less(na, nb);
      auto  min_na_nb = eve::if_else(less_nanb, na, nb);

      auto br_negint =  [&](auto n, auto t){ // (a == -na) or (b == -nb)
        auto term = kyosu::one(as<r_t>());
        auto sum = term;
        auto nn =  if_else(t,  n, zero);
        auto mnn = int(eve::maximum(nn));
        for (int n = 0 ; n < mnn ; ++n)
        {
          term *= kyosu::if_else(n < nn, z*(a+n)*(b+n)/(eve::inc(n)*(c+n)), zero);
          sum +=  term;
        }
        return sum;
      };

      auto br_else =  [&](){
        auto term = kyosu::one(as<r_t>());
        auto sum = term;
        auto  dcv_tab = dcv_poly_calc(a,b,c,z);
        auto min_n = min_n_calc(dcv_tab);
        auto possible_false_cv = kyosu::true_(kyosu::as<r_t>())&& !notdone;
        for(int n = 0;  n < maxit; ++n)
        {
          term *= z*(a+n)*(b+n)/(eve::inc(n)*(c+n));
          sum += term;
          auto terminated = (!possible_false_cv &&  (kyosu::linfnorm (term) <=  eve::eps(as<u_t>()))) || !notdone;
          if (eve::all(terminated)) return sum;
          possible_false_cv = kyosu::if_else(possible_false_cv && (n >= min_n)
                                            , eve::is_gtz(dcv_calc(dcv_tab,u_t(n)))
                                            , possible_false_cv);
        }
        return kyosu::nan(as<r_t>());
      };

      auto r = kyosu::nan(as<r_t>());
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_negint, notdone, tab, r, min_na_nb, tab);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_negint, notdone, ta, r, na, ta);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_negint, notdone, tb, r, nb, tb);
            if( eve::any(notdone) )
            {
              last_interval(br_else, notdone, r);
            }
          }
        }
      }
      return r;
    }
  }


  auto hyp_ps_zero (auto a, auto b, auto c, auto z) noexcept
  {
    using r_t = decltype(a+b+c+z);
    return hyp_ps_zero(a, b, c, z, kyosu::true_(eve::as<r_t>()));
  }
}
