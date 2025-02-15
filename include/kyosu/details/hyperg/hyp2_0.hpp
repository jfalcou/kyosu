//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/functions/is_flint.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  confluent hypergeometric limit function
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  // only works for aa having at least one non positive integer component  else the serie diverges
  template<typename Z,
           kumi::sized_product_type<2> T1,
           kumi::sized_product_type<0> T2>
  KYOSU_FORCEINLINE  auto
  hyperg(Z z, T1 aa , T2 bb)
  {
    constexpr int N = 1;
    using r_t = decltype(kumi::get<0>(aa)+kumi::get<1>(aa)+z);
    r_t a1 = kumi::get<0>(aa);
    r_t a2 = kumi::get<1>(aa);
    auto ra1 = kyosu::real(a1);
    auto ra2 = kyosu::real(a2);
    auto test1 = kyosu::is_flint(a1) && eve::is_lez(ra1);
    auto test2 = kyosu::is_flint(a2) && eve::is_lez(ra2);
    auto convergent = (test1 || test2 || is_eqz(z));
    ra1 = kyosu::if_else(convergent, ra1, zero);
    ra2 = kyosu::if_else(convergent, ra2, zero);
    using u_t = eve::underlying_type_t<r_t>;
    auto n = int(eve::maximum(eve::max(-ra1, -ra2)));
    r_t a(1), s(1);
    for (int j=0; j <= n;)
    {
      auto p = (ra1*ra2)*z;
      auto pz = kyosu::is_eqz(p);
      if (eve::all(pz)) break;
      a *= p/(++j);
      ra1 = inc(ra1);
      ra2 = inc(ra2);
      s += a;
    }
    return if_else(convergent, s, allbits);
  }
}
