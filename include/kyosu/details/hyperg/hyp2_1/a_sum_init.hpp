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

  auto A_sum_init(auto m, auto eps, auto gamma_inv_one_meps) -> decltype(m+eps+gamma_inv_one_meps)
  {
    using r_t = decltype(m+eps+gamma_inv_one_meps);

//     if constexpr(eve::scalar_value<r_t>)
//     {
//       const r_t one_meps = kyosu::oneminus(eps);
//       if (one_meps-m != oneminus(m))
//       {
//         r_t gamma_inv_one_meps_mm = gamma_inv_one_meps;
//         for (int i = 1 ; i <= m ; ++i) gamma_inv_one_meps_mm *= one_meps - i;
//         return gamma_inv_one_meps_mm/eps;
//       }
//       else
//       {
//         auto rm =  real(m);
//         return r_t(eve::sign_alternate(rm)*eve::factorial(dec(rm)));
//       }
//     }
//     else //simd
    {
      r_t  one_meps(kyosu::oneminus(eps));
      auto br_diff = [&](){
        r_t  gamma_inv_one_meps_mm(gamma_inv_one_meps);
        auto mm = int(eve::maximum(real(m)));
        for (int i=1; i<=mm; ++i) gamma_inv_one_meps_mm *= kyosu::if_else(i <= real(m), one_meps - i, one);
        return gamma_inv_one_meps_mm/eps;
      };
      auto br_else = [m](){// (-1)^m (m-1)!
        auto rm =  real(m);
        return r_t(eve::sign_alternate(rm)*eve::factorial(dec(rm)));
      };
      auto diff = (one_meps-m != kyosu::oneminus(m));
      auto r       = kyosu::nan(kyosu::as<r_t>());
      auto notdone = kyosu::is_nan(r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_diff, notdone, diff, r);
        if( eve::any(notdone) )
        {
          notdone = last_interval(br_else, notdone, r);
        }
      }
      return r;
    }
  }

  auto log_A_sum_init (auto m, auto eps)
  {
    using r_t = decltype(m+eps);
    using u_t = eve::underlying_type_t<r_t>;

    if constexpr(eve::scalar_value<r_t>)
    {
      using u_t = eve::underlying_type_t<r_t>;
      const r_t one_meps_mm = kyosu::oneminus(m+eps);

      if (one_meps_mm != kyosu::oneminus(m)){
        return (-kyosu::log_gamma (one_meps_mm) - kyosu::log(eps));
      }
      else
      {
        u_t lfact(eve::lfactorial(u_t(m)));
        auto i_piorzero = if_else(eve::is_even(real(m)), zero, (complex(u_t(0), u_t(eve::pi(as<u_t>())))));
        return lfact + i_piorzero;
      }
    }
    else
    {
      auto one_meps_mm = oneminus(m+eps);

      auto br_diff =  [&](){// (one_meps_mm != 1-m)
        if constexpr(kyosu::concepts::real<r_t>)
        return (-eve::log_gamma(one_meps_mm) - eve::log(eps));
        else
          return (-kyosu::log_gamma(one_meps_mm) - kyosu::log(eps));
      };

      auto br_else =  [&](){ // (one_meps_mm == 1-m)
        r_t lfact(eve::lfactorial(real(m)));
        if constexpr(kyosu::concepts::real<r_t>) return lfact;
        else
        {
          auto i_piorzero = if_else(eve::is_even(real(m)), zero, (complex(u_t(0), u_t(eve::pi(as<u_t>())))));
          return lfact + i_piorzero;
        }
      };

      auto diff = (one_meps_mm != kyosu::oneminus(m));
      auto r       = kyosu::nan(kyosu::as<r_t>());
      auto notdone = kyosu::is_nan(r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_diff, notdone, diff, r);
        if( eve::any(notdone) )
        {
          notdone = last_interval(br_else, notdone, r);
        }
      }
      return r;
    }
  }
}
