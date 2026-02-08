//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/constants/cinf.hpp>
#include <kyosu/functions/linfnorm.hpp>
#include <kyosu/functions/is_not_flint.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  confluent hypergeometric limit function 0F1({}; {b0, b1}; z)
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  template<typename Z, eve::sized_product_type<0> T1, eve::sized_product_type<2> T2>
  KYOSU_FORCEINLINE auto hyperg(Z z, T1, T2 bb)
  {
    using r_t = decltype(kumi::get<0>(bb) + kumi::get<1>(bb) + z);
    using u_t = eve::underlying_type_t<r_t>;
    r_t b0 = kumi::get<0>(bb);
    r_t b1 = kumi::get<1>(bb);
    auto tol = eve::eps(eve::as<u_t>());

    constexpr size_t Maxit = 500;

    auto br_serie = [&](auto test0) {
      auto zz = kyosu::if_else(test0, z, zero);

      r_t rb01 = kyosu::rec(b0 * b1);
      r_t r1 = rb01;
      r_t r2 = rec(2 * inc(b0) * inc(b1));

      r_t s1 = inc(zz * r1);
      r_t s2 = s1 + kyosu::sqr(zz) * r2 * rb01;
      r_t s3{};
      auto test = kyosu::false_(as<r_t>());
      for (size_t j = 3; j <= Maxit; ++j)
      {
        auto r = rec(j * (b0 + j - 1) * (b1 + j - 1));
        s3 = s2 + (s2 - s1) * r * zz;
        test = eve::is_not_greater(kyosu::linfnorm[kyosu::flat](s3 - s2), kyosu::linfnorm[kyosu::flat](s2) * tol);
        if (eve::all(test)) return s3;
        s1 = s2;
        s2 = s3;
      }
      return kyosu::if_else(test, s3, allbits);
      ;
    };

    auto br_rest = []() { return kyosu::cinf(eve::as<r_t>()); };

    r_t r = kyosu::nan(eve::as<r_t>());
    r = if_else(is_eqz(z), one, r);
    auto notdone = kyosu::is_nan(r);
    auto b0_notnegint = is_not_flint(b0) || eve::is_nlez(real(b0));
    auto b1_notnegint = is_not_flint(b1) || eve::is_nlez(real(b1));
    auto nongi = b0_notnegint && b1_notnegint;
    if (eve::any(notdone))
    {
      notdone = next_interval(br_serie, notdone, nongi, r, nongi);
      if (eve::any(notdone)) { last_interval(br_rest, notdone, r); }
    }
    return r;
  }

}
