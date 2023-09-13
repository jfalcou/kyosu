//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  Unary functions : tgamma
  //===-------------------------------------------------------------------------------------------
  template<kyosu::concepts::complex Z>
  auto dispatch(eve::tag_of<kyosu::tgamma>, Z const& a0) noexcept
  {
    // 15 sig. digits for 0<=real(z)<=171
    // coeffs should sum to about g*g/2+23/24
    //
    using r_t = eve::element_type_t<as_real_t<Z>>;
    auto  g=r_t(607)/r_t(128);
    // best results when 4<=g<=5
    constexpr int N = 15;
    std::array<r_t, N>  c =
      {  0.99999999999999709182,
         57.156235665862923517,
         -59.597960355475491248,
         14.136097974741747174,
         -0.49191381609762019978,
         .33994649984811888699e-4,
         .46523628927048575665e-4,
         -.98374475304879564677e-4,
         .15808870322491248884e-3,
         -.21026444172410488319e-3,
         .21743961811521264320e-3,
         -.16431810653676389022e-3,
         .84418223983852743293e-4,
         -.26190838401581408670e-4,
         .36899182659531622704e-5
      };

    //Num Recipes used g=5 with 7 terms
    //for a less effective approximation

    auto negra0 = eve::is_negative(real(a0));
    auto z = if_else(negra0, -a0, a0);
    z = dec(z);
    auto zh = z+eve::half(eve::as<r_t>());
    auto zgh=zh+g;
    //trick for avoiding FP overflow above z=141
    auto zp=pow(zgh,(zh*eve::half(eve::as<r_t>())));
    auto ss = Z{0, 0};
    for(int pp = N-1; pp >= 1; --pp){
      ss+= c[pp]/(z+pp);
    }
    auto sq2pi = r_t(2.5066282746310005024157652848110);
    auto f=(sq2pi*(c[0]+ss))*((zp*exp(-zgh))*zp);
    auto o = eve::one(eve::as<r_t>());
    f = if_else(is_eqz(z) || z == o, o, f);
    //adjust for negative real parts
    auto reala0 = is_real(a0);
    if(eve::any(negra0))
    {
      f = if_else(negra0, rec(-eve::inv_pi(eve::as(real(a0)))*a0*f*sinpi(a0)), eve::zero);
      f = if_else (negra0 && reala0 && eve::is_flint(real(a0)), to_complex(eve::nan(eve::as(sq2pi)), eve::inf(eve::as(sq2pi))), f);
    }
    f = if_else(eve::is_gtz(real(a0)) && eve::is_flint(real(a0)) && reala0, to_complex(eve::nearest(real(f))), f);
    f = if_else (is_eqz(a0), to_complex(eve::inf(eve::as(g))*eve::pedantic(eve::signnz)(real(a0))), f);
    return f;
  }

  //===-------------------------------------------------------------------------------------------
   //  Unary functions : log_gamma
   //===-------------------------------------------------------------------------------------------
   template<kyosu::concepts::complex Z>
   EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::log_abs_gamma>, Z const& a0) noexcept
   {
     return log_abs(tgamma(a0));
   }

   template<kyosu::concepts::complex Z>
   auto dispatch(eve::tag_of<kyosu::log_gamma>, Z const& a0) noexcept
   {
     // 15 sig. digits for 0<=real(z)<=171
     // coeffs should sum to about g*g/2+23/24
     //
     using r_t = eve::element_type_t<as_real_t<Z>>;
     auto  g=r_t(607)/r_t(128);
     // best results when 4<=g<=5
     constexpr int N = 15;
     std::array<r_t, N>  c =
       {  0.99999999999999709182,
          57.156235665862923517,
          -59.597960355475491248,
          14.136097974741747174,
          -0.49191381609762019978,
          .33994649984811888699e-4,
          .46523628927048575665e-4,
          -.98374475304879564677e-4,
          .15808870322491248884e-3,
          -.21026444172410488319e-3,
          .21743961811521264320e-3,
          -.16431810653676389022e-3,
          .84418223983852743293e-4,
          -.26190838401581408670e-4,
          .36899182659531622704e-5
       };

     //Num Recipes used g=5 with 7 terms
     //for a less effective approximation

     auto negra0 = eve::is_negative(real(a0));
     auto z = if_else(negra0, -a0, a0);
     Z ss{};
     for(int pp = N-1; pp >= 1; --pp){
       ss += c[pp]*rec(z+dec(pp));
     }
     auto zg = z+g-eve::half(eve::as(g));
     auto lsq2pi = r_t(0.9189385332046727417803297);
     auto f=(lsq2pi + log(c[0]+ss)) - zg + (z-eve::half(eve::as<r_t>()))*log(zg);
     auto zer = eve::zero(eve::as(g));
     auto o = eve::one(eve::as(g));
     auto t = o+o;
     f = if_else(z == t|| z == o, zer, f);
     //adjust for negative real parts
     if(eve::any(negra0))
     {
       auto lpi = r_t(1.14472988584940017414342735);
       auto reala0 = is_real(a0);
       f = kyosu::if_else(negra0, lpi-log(a0*sinpi(-a0))-f, f);
       f = kyosu::if_else (negra0 && reala0 && eve::is_flint(real(a0))
                          , to_complex(eve::nan(eve::as(g)), eve::inf(eve::as(g)))
                          , f);
     }
     return f;
   }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : digamma
  //===-------------------------------------------------------------------------------------------
  template<kyosu::concepts::complex Z>
  auto dispatch(eve::tag_of<kyosu::digamma>, Z const& a0) noexcept
  {
    // 15 sig. digits for 0<=real(z)<=171
    // coeffs should sum to about g*g/2+23/24
    //
    using r_t = eve::element_type_t<as_real_t<Z>>;
    auto  g=r_t(607)/r_t(128);
    // best results when 4<=g<=5
    constexpr int N = 15;
    std::array<r_t, N>  c =
      {  0.99999999999999709182,
         57.156235665862923517,
         -59.597960355475491248,
         14.136097974741747174,
         -0.49191381609762019978,
         .33994649984811888699e-4,
         .46523628927048575665e-4,
         -.98374475304879564677e-4,
         .15808870322491248884e-3,
         -.21026444172410488319e-3,
         .21743961811521264320e-3,
         -.16431810653676389022e-3,
         .84418223983852743293e-4,
         -.26190838401581408670e-4,
         .36899182659531622704e-5
      };

    //Num Recipes used g=5 with 7 terms
    //for a less effective approximation

    auto reflection = real(a0) < eve::half(eve::as(real(a0)));
    auto z = if_else(reflection, oneminus(a0), a0);

    Z d{};
    auto n = d;
    for(int pp = N-1; pp >= 1; --pp){
      auto dz = rec(z+dec(pp));
      auto dd =  c[pp]*dz;
      d += dd;
      n -= dd*dz;
    }
    d+= c[0];
    auto zg = z+g-eve::half(eve::as(g));
    auto f = log(zg) + (n/d - g/zg);

    if(eve::any(reflection))
    {
      f = if_else(reflection, f-eve::pi(eve::as(g))*cotpi(a0), f);
      f = if_else (reflection && is_real(a0) && eve::is_flint(real(a0))
                  , to_complex(eve::nan(eve::as(g)), eve::inf(eve::as(g))), f);
    }
    return f;
  }

//   //===-------------------------------------------------------------------------------------------
//   //  Unary functions : zeta
//   //===-------------------------------------------------------------------------------------------
//   template<kyosu::concepts::complex Z>
//   EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::zeta>, Z const& z) noexcept
//   {
//     auto zz=exp2(z);
//     auto k = zz/(zz-2);
//     return if_else(z == one(eve::as(z)), Z(inf(eve::as(real(z))), 0), k*eta(z));
//   }

//   //===-------------------------------------------------------------------------------------------
//   //  Binary functions : rising_factorial, lrising_factorial, lbeta, beta
//   //===-------------------------------------------------------------------------------------------
//   template<kyosu::concepts::complex Z1, kyosu::concepts::complex Z2 >
//   EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::rising_factorial>
//                                              , Z1 const& a0, Z2 const& a1) noexcept
//   {
//     return if_else(is_eqz(a1), one, pedantic(div)(tgamma(a0+a1),tgamma(a0)));
//   }

//   template<kyosu::concepts::complex Z1, kyosu::concepts::complex Z2 >
//   EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::lrising_factorial_
//                                              , Z1 const& a0, Z2 const& a1) noexcept
//   {
//     return  if_else(is_eqz(a1), zero, log( pedantic(div)(tgamma(a0+a1),tgamma(a0))));
//   }

//   template<kyosu::concepts::complex Z1, kyosu::concepts::complex Z2 >
//   EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::lbeta_

//   {
//     return log(beta(a0, a1));
//   }

//   template<kyosu::concepts::complex Z1, kyosu::concepts::complex Z2 >
//   EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::beta_
//                                              , Z1 const& a0, Z2 const& a1) noexcept
//   {
//     auto y = a0 + a1;
//     return tgamma(a0)*tgamma(a1)/tgamma(y);
//   }


//  }

// #include <eve/module/complex/detail/special/erf.hpp>
// #include <eve/module/complex/detail/special/erfcx.hpp>

}
