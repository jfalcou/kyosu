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
  
  KYOSU_FORCEINLINE auto dcv_poly_calc(auto a,auto b,auto c,auto z)
  {
    auto mod_a2 = sqr_abs(a);
    auto mod_b2 = sqr_abs(b);
    auto mod_c2 = sqr_abs(c);
    auto mod_z2 = sqr_abs(z);
    auto re_a = real(a);
    auto re_b = real(b);
    auto re_c = real(c);
    
    auto dcv0 = 2.0*((re_a*mod_b2 + re_b*mod_a2)*mod_z2 - re_c - mod_c2);
    auto dcv1 = 2.0*(eve::dec((mod_a2 + mod_b2 + 4.0*re_a*re_b)*mod_z2) - 4*re_c - mod_c2);
    auto dcv2 = 6.0*(eve::dec((re_a + re_b)*mod_z2 - re_c));
    auto dcv3 = 4.0*eve::dec(mod_z2);
    return kumi::tuple{dcv0,dcv1,dcv2,dcv3};
  }
  
  KYOSU_FORCEINLINE auto dcv_calc(auto dcv_coefs, auto x)
  {
    return reverse_horner(x, dcv_coefs);
  }
  
  KYOSU_FORCEINLINE auto min_n_calc (auto dcv_coefs)
  {
    auto c1 = get<1>(dcv_coefs);
    auto c2 = get<2>(dcv_coefs);
    auto three_c3 = 3*get<3>(dcv_coefs);
    auto delta = sqr(c2) - three_c3*c1;
    auto test = eve::is_gez(delta);
    auto sqrtdelta = if_else(test, eve::sqrt(delta), zero);
    auto largest_root = if_else(test, -(c2 + sqrtdelta)/three_c3, zero);
    return eve::max(ceil(largest_root),eve::zero(eve::as(c1)));
  }
  
}
