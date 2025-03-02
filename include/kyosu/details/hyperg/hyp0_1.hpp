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
#include <kyosu/functions/tgamma_inv.hpp>
#include <kyosu/details/hyperg/is_negint.hpp>


namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  confluent hypergeometric limit function 0F1({}; {b}; z)
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  template<typename Z,
           kumi::sized_product_type<0> T1,
           kumi::sized_product_type<1> T2>
  KYOSU_FORCEINLINE  auto
  hyperg(Z z, T1, T2 aa)
  {
    using r_t = decltype(kumi::get<0>(aa)+z);
    using u_t = eve::underlying_type_t<r_t>;
    r_t a = kumi::get<0>(aa);
    auto tol = eve::eps(eve::as<u_t>());
    constexpr size_t Maxit = 500;

    auto br_serie =  [&](auto test0){
      auto zz = kyosu::if_else(test0,  z, zero);

      r_t ra = kyosu::rec(a);
      r_t r1 = ra;
      r_t r2 = rec(2*inc(a));

      r_t s1 = inc(zz*r1);
      r_t s2 = s1 + kyosu::sqr(zz)*r2*ra;
      r_t s3{};
      auto test = kyosu::false_(as<r_t>());
      for (size_t j=3; j <= Maxit; ++j)
      {
        auto r = rec(j*(a+j-1));
        s3 = s2 + (s2-s1)*r*zz;
        test = eve::is_not_greater(kyosu::linfnorm[kyosu::flat](s3-s2), kyosu::linfnorm[kyosu::flat](s2)*tol);
        if (eve::all(test)) return s3;
        s1 = s2;
        s2 = s3;
      }
      return kyosu::if_else(test, s3, allbits);;
    };

    auto br_rest =  [](){
      return kyosu::cinf(eve::as<r_t>());
    };

    r_t r =  kyosu::nan(eve::as<r_t>());
    r = if_else(is_eqz(z), one, r);
    auto notdone = kyosu::is_nan(r);
    auto a_notnegint = !is_negint(a);
    notdone = notdone || a_notnegint;

    if( eve::any(notdone) )
    {
      notdone = next_interval(br_serie, notdone, a_notnegint, r, a_notnegint);
      if( eve::any(notdone) )
      {
        last_interval(br_rest, notdone, r);
      }
    }
    return r;
  }

  template<typename Z,
           kumi::sized_product_type<0> T1,
           kumi::sized_product_type<1> T2>
  KYOSU_FORCEINLINE  auto
  hyperg(Z z, T1, T2 cc, decltype(kyosu::regularized) )
  {
    using r_t = decltype(kumi::get<0>(T2())+z);
    r_t c(kumi::get<0>(cc));
    c = if_else(is_negint(c), eve::next(real(c)), c);
    return  hyperg(z, kumi::tuple{}, kumi::tuple{c})*kyosu::tgamma_inv(c);
  }
}
