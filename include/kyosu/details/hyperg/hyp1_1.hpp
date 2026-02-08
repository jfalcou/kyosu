//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/functions/linfnorm.hpp>
#include <kyosu/constants/wrapped.hpp>
#include <kyosu/functions/is_flint.hpp>
#include <kyosu/functions/tgamma_inv.hpp>
#include <kyosu/constants/cinf.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //   hypergeometric 1F1
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  template<typename Z, eve::sized_product_type<1> T1, eve::sized_product_type<1> T2>
  KYOSU_FORCEINLINE auto hyperg(Z zz, T1 bb, T2 aa)
  {
    using r_t = decltype(kumi::get<0>(aa) + kumi::get<0>(bb) + zz);
    r_t a(kumi::get<0>(bb));
    r_t b(kumi::get<0>(aa));
    using u_t = eve::underlying_type_t<r_t>;
    auto tol = eve::eps(eve::as<u_t>());
    constexpr size_t Maxit = 100000;
    auto anegint = kyosu::is_flint(a) && eve::is_lez(real(a));
    auto bnegint = kyosu::is_flint(b) && eve::is_lez(real(b));
    auto abnegint = (bnegint && !anegint) || (bnegint && anegint && (real(a) < real(b)));

    auto br_abnegint = [&]() { return kyosu::cinf(eve::as<r_t>()); };

    auto br_anegint = [&]() {
      auto aa = kyosu::if_else(anegint, a, zero);
      int n = eve::maximum(-real(a));
      r_t a1(1), s(1);
      for (size_t j = 1; j <= n; ++j)
      {
        a1 *= (kyosu::dec(aa + j) / (kyosu::dec(b + j) * j)) * zz;
        s += a1;
      }
      return s;
    };

    auto br_zero = [&](auto test) {
      auto z = kyosu::if_else(test, zz, zero);
      auto r1 = a / b;
      auto r2 = kyosu::inc(a) / (2 * kyosu::inc(b));
      r_t s1 = kyosu::inc(z * r1);
      r_t s2 = s1 + kyosu::sqr(z) * (r1)*r2;
      r_t s3{};
      auto smallp = kyosu::false_(as<r_t>());

      for (size_t j = 3; j <= Maxit; ++j)
      {
        auto r = kyosu::dec(a + j) / (j * kyosu::dec(b + j));
        s3 = s2 + (s2 - s1) * r * z;
        auto small = kyosu::linfnorm[kyosu::flat](s3 - s2) < kyosu::linfnorm[kyosu::flat](s1) * tol;
        if (eve::all(small && smallp)) return s3;
        s1 = s2;
        s2 = s3;
        smallp = small;
      }
      return if_else(smallp, s3, allbits);
    };

    r_t r = kyosu::nan(eve::as<r_t>());
    auto notdone = kyosu::is_nan(r);

    if (eve::any(notdone))
    {
      notdone = next_interval(br_abnegint, notdone, abnegint, r);
      if (eve::any(notdone))
      {
        notdone = next_interval(br_anegint, notdone, anegint, r);
        if (eve::any(notdone)) { notdone = last_interval(br_zero, notdone, r, notdone); }
      }
      return r;
    }
  }

  template<typename Z, eve::sized_product_type<1> T1, eve::sized_product_type<1> T2>
  KYOSU_FORCEINLINE auto hyperg(Z z, T1 aa, T2 cc, decltype(kyosu::regularized))
  {
    using r_t = decltype(kumi::get<0>(aa) + kumi::get<0>(cc) + z);
    r_t c(kumi::get<0>(cc));
    auto isnegint = kyosu::is_real(c) && eve::is_flint(kyosu::real(c)) && eve::is_ltz(kyosu::real(c));
    c = if_else(isnegint, eve::next(real(c)), c);
    return hyperg(z, aa, kumi::tuple{c}) * kyosu::tgamma_inv(c);
  }
}
