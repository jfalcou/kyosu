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
  auto  gamma_inv_diff_eps(auto z, auto eps, auto notdone)
  {
    using r_t = decltype(z+eps);
    using u_t = eve::underlying_type_t<r_t>;

    r_t epspz = z + eps;
    auto x = real(z);
    auto eps_px(real(epspz));
    auto n = eve::nearest(x);
    auto m = eve::nearest(eps_px);

    auto is_z_negative_integer = (z == n) && eve::is_lez(n);
    auto is_epspz_negative_integer = (epspz == m) && (m <= 0);
    auto z_neg_int_distance = kyosu::linfnorm(z + kyosu::abs(n));
    auto epspz_neg_int_distance = kyosu::linfnorm(epspz + kyosu::abs(m));
    auto r       = kyosu::nan(kyosu::as<r_t>());

    auto br_gt01 = [&](){  //    kyosu::linfnorm(eps) > u_t(0.1))
      return   (kyosu::tgamma_inv (z) - kyosu::tgamma_inv (epspz))/eps;
    };

    auto br_epspzneqz = [&](){// (epspz != z)


      auto br_is_z_negative_integer = [&](){
        return -tgamma_inv(epspz)/eps;
      };
      auto br_is_epspz_negative_integer = [&](){
        return tgamma_inv(z)/eps;
      };
      auto br_z_neg_int_distance_lt_epspz_neg_int_distance =  [&](){
        return  r_t(gamma_ratio_diff_small_eps(z,eps, notdone)*kyosu::tgamma_inv(epspz));
      };
      auto br_else  = [&](){
        return r_t(gamma_ratio_diff_small_eps(epspz,-eps, notdone)*tgamma_inv (z));
      };

      if( eve::any(notdone) )
      {
        notdone = next_interval(br_is_z_negative_integer, notdone,is_z_negative_integer , r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_is_epspz_negative_integer, notdone, is_epspz_negative_integer, r);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_z_neg_int_distance_lt_epspz_neg_int_distance, notdone, z_neg_int_distance < epspz_neg_int_distance , r);
            if( eve::any(notdone) )
            {
              notdone = last_interval(br_else, notdone, r);
            }
          }
        }
      }
      return r;
    };

    auto is_z_and_epspz_negative_integers = is_z_negative_integer && is_epspz_negative_integer;

    auto br_is_z_and_epspz_negative_integers =  [&](){// (is_z_negative_integer && is_epspz_negative_integer)

      auto an = if_else(is_z_and_epspz_negative_integers, eve::abs(real(z)), zero);
      auto f = eve::factorial(an);
      return r_t(eve::sign_alternate(an+1)*f); //(-1)^(n+1) n!
    };

    auto br_final =  [&](){
      return gamma_ratio_diff_small_eps(z,eps, notdone)*kyosu::tgamma_inv(epspz);
    };

    if( eve::any(notdone) )
    {
      notdone = next_interval(br_gt01, notdone, kyosu::linfnorm(eps) > u_t(0.1), r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_epspzneqz, notdone, (epspz != z), r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_is_z_and_epspz_negative_integers, notdone, is_z_and_epspz_negative_integers, r);
          if( eve::any(notdone) )
          {
            notdone = last_interval(br_final, notdone, r);
          }
        }
      }
    }
    return r;
  }
}
