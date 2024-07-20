//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <type_traits>
#include <eve/module/core.hpp>

namespace kyosu::_
{
  KYOSU_FORCEINLINE
  auto minus_log10_cyl_j_at_infinity( auto n, auto az ) {
    // Auxiliary function to calculate -log( Jn(x->INF) ).
    using u_t = decltype(az);
    return u_t(0.5)*eve::log10(u_t(6.28)*n) - n*eve::log10(u_t(1.36)*az/n);
  };

  KYOSU_FORCEINLINE
  auto ini_for_br_1(auto az, auto mg)
  {
    // Starting point for backward recurrence
    //  for when |Jn(x)|~10e-mg
    //  using the secant method.
    using u_t = decltype(az);
    auto n0 = inc(eve::ceil( u_t(1.1)*az));
    auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - mg;
    auto n1 = n0 + 5;
    auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - mg;
    auto nn = n1 - (n1 - n0)/oneminus(f0/f1);
    auto f = minus_log10_cyl_j_at_infinity(nn, az) - mg;
    auto test = eve::abs(nn - n1) > 1;
    while ( eve::any(test) )
    {
      n0 = n1;
      f0 = f1;
      n1 = nn;
      f1 = f;
      nn = eve::if_else(test, n1 - (n1 - n0)/oneminus(f0/f1), nn);
      f =  eve::if_else(test, minus_log10_cyl_j_at_infinity(nn, az) - mg, f);
      test =  eve::abs(nn - n1) > 1;
    }
    return eve::trunc(nn);
  };

  KYOSU_FORCEINLINE
  auto ini_for_br_2(auto n, auto az, auto sd){
    using u_t = decltype(az);
    // Starting point for backward recurrence
    //  for when Jn(x) has sd significant digits
    //  using the secant method.
    auto hmp = eve::half(eve::as<u_t>())*sd;
    auto ejn = minus_log10_cyl_j_at_infinity(n, az);
    auto t = ejn <= hmp;
    auto obj = eve::if_else(t, sd, hmp+ejn);
    auto n0  = eve::if_else(t, eve::ceil(u_t(1.1)*az), u_t(n));
    auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - obj;
    auto n1 = n0 + 5;
    auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - obj;
    auto nn = n1 - (n1-n0)/oneminus(f0/f1);
    auto f = minus_log10_cyl_j_at_infinity(nn, az) - obj;
    auto test = eve::abs(nn - n1) >= 1;
    while ( eve::any(test))
    {
      n0 = n1;
      f0 = f1;
      n1 = nn;
      f1 = f;
      nn = eve::if_else(test, n1 - (n1-n0)/(oneminus(f0/f1)), nn);
      f  = eve::if_else(test, minus_log10_cyl_j_at_infinity(nn, az) - obj, f);
      test = eve::abs(nn - n1) >= 1;
    }
    return eve::trunc(nn + 10);
  };
}
