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
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  1F0({a}; {}; z) = (1-z)^(-a)
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  template<typename Z, eve::sized_product_type<1> T1, eve::sized_product_type<0> T2>
  KYOSU_FORCEINLINE auto hyperg(Z z, T1 aa, T2)
  {
    using r_t = decltype(kumi::get<0>(aa) + z);
    r_t a = kumi::get<0>(aa);
    using u_t = eve::underlying_type_t<r_t>;
    auto testsmall = abs(z) < eve::eps(as<u_t>());
    auto r = if_else(testsmall, kyosu::inc(a * z), kyosu::pow(kyosu::oneminus(z), -a));
    auto test = kyosu::is_real(z) && is_real(a) && (real(a) > kyosu::one(eve::as<u_t>()));
    if (eve::any(test)) kyosu::real(r) = kyosu::if_else(test, one, kyosu::real(r));
    return r;
  }
}
