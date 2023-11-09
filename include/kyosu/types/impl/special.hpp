//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <kyosu/details/cayleyify.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //  Unary functions : tgamma
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::tgamma>, Z const& a0) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using r_t = eve::element_type_t<as_real_type_t<Z>>;
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
      auto ss = Z{};
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
        f = if_else (negra0 && reala0 && eve::is_flint(real(a0)), complex(eve::nan(eve::as(sq2pi)), eve::inf(eve::as(sq2pi))), f);
      }
      f = if_else (reala0, complex(eve::tgamma(real(a0))), f);
      f = if_else (eve::is_nan(real(f)), complex(eve::nan(eve::as(sq2pi)), eve::inf(eve::as(sq2pi))), f);
      f = if_else (is_eqz(a0), complex(eve::inf(eve::as(g))*eve::pedantic(eve::signnz)(real(a0))), f);
      return f;
    }
    else
    {
      return cayley_extend(tgamma, a0);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : log_gamma
  //===-------------------------------------------------------------------------------------------
  template<kyosu::concepts::complex Z>
  EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::log_abs_gamma>, Z const& a0) noexcept
  {
    return log_abs(tgamma(a0));
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::log_gamma>, Z const& a0) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using r_t = eve::element_type_t<as_real_type_t<Z>>;
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
        ss += c[pp]*rec(z+eve::dec(pp));
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
                           , complex(eve::nan(eve::as(g)), eve::inf(eve::as(g)))
                           , f);
      }
      return f;
    }
    else
    {
      return cayley_extend(log_gamma, a0);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : digamma
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::digamma>, Z const& a0) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using r_t = eve::element_type_t<as_real_type_t<Z>>;
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
        auto dz = rec(z+eve::dec(pp));
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
                    , complex(eve::nan(eve::as(g)), eve::inf(eve::as(g))), f);
      }
      return f;
    }
    else
    {
      return cayley_extend(digamma, a0);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  Binary functions : rising_factorial, lrising_factorial, lbeta, beta
  //===-------------------------------------------------------------------------------------------
  // WAITING FOR DECORATORS
  template<typename Z1, typename Z2>
  auto dispatch(eve::tag_of<kyosu::rising_factorial>
               , Z1 const& a0, Z2 const& a1) noexcept
  requires (kyosu::concepts::complex<Z1> || kyosu::concepts::complex<Z2>)
  {
    using r_t = as_cayley_dickson_t<Z1, Z2>;
    return kyosu::if_else(is_eqz(a1), r_t(1), tgamma(a0+a1)/tgamma(a0)); //pedantic(div)(tgamma(a0+a1),tgamma(a0)));
  }

  template<typename Z1, typename Z2>
  auto dispatch(eve::tag_of<kyosu::lrising_factorial>
               , Z1 const& a0, Z2 const& a1) noexcept
  {
    using r_t = as_cayley_dickson_t<Z1, Z2>;
    return  kyosu::if_else(is_eqz(a1), r_t{}, log(tgamma(a0+a1)/tgamma(a0))); //pedantic(divide)(tgamma(a0+a1),tgamma(a0))));
  }

  template<typename Z1, typename Z2>
  auto dispatch(eve::tag_of<kyosu::lbeta>, Z1 const& a0, Z2 const& a1) noexcept
  {
    return log(beta(a0, a1));
  }

  template<typename Z1, typename Z2>
  auto dispatch(eve::tag_of<kyosu::beta>, Z1 const& a0, Z2 const& a1) noexcept
  {
    auto y = a0 + a1;
    return tgamma(a0)*tgamma(a1)/tgamma(y);
  }

  template<eve::unsigned_scalar_value K, typename Z>
  auto dispatch(eve::tag_of<kyosu::deta>
               , K const & kk
               , Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // 15 sig. digits for 0<=real(z)<=171
      // coeffs should sum to about g*g/2+23/24
      //
      using v_t = kyosu::as_real_type_t<Z>;
      using real_t = eve::element_type_t<v_t>;
      auto k = real_t(kk);
      auto [rz, iz] = z;
      auto iszero = is_eqz(z);
      auto isreal = eve::is_eqz(iz);
      auto isneg  = eve::is_ltz(rz);
      auto isnegreal = isreal && isneg;
      auto isodd  = isnegreal && eve::is_odd(rz);
      auto iseven = isnegreal && eve::is_even(rz);

      auto r=eve::half(eve::as(rz)); // reflection point
      auto reflect = rz < r;
      z =  if_else(reflect, oneminus(z), z);

      std::array<real_t, 64> cm = {
        .27105054312137610850e-19
        -.17889335846010823161e-17,
        .58167446553847312884e-16,
        -.12421162189080181548e-14,
        .19593322190397666205e-13,
        -.24347803504257137241e-12,
        .24823251635643084345e-11,
        -.21352608103961806529e-10,
        .15816215942184366772e-9,
        -.10246226511017621219e-8,
        .58768014045093054654e-8,
        -.30137695171547022183e-7,
        .13931171712321674741e-6,
        -.58440580661848562719e-6,
        .22376124247437700378e-5,
        -.78585149263697370338e-5,
        .25423835243950883896e-4,
        -.76053287924037718971e-4,
        .21106516173760261250e-3,
        -.54504190222378945440e-3,
        .13131884053420191908e-2,
        -.29592166263096543401e-2,
        .62512730682449246388e-2,
        -.12405987285776082154e-1,
        .23176737166455607805e-1,
        -.40840766970770029873e-1,
        .68016197438946063823e-1,
        -.10726959700408922397,
        .16054206784249779846,
        -.22851039270529494523,
        .31007238254065152134,
        -.40215850009669926857,
        .50000000000000000000,
        -.59784149990330073143,
        .68992761745934847866,
        -.77148960729470505477,
        .83945793215750220154,
        -.89273040299591077603,
        .93198380256105393618,
        -.95915923302922997013,
        .97682326283354439220,
        -.98759401271422391785,
        .99374872693175507536,
        -.99704078337369034566,
        .99868681159465798081,
        -.99945495809777621055,
        .99978893483826239739,
        -.99992394671207596228,
        .99997457616475604912,
        -.99999214148507363026,
        .99999776238757525623,
        -.99999941559419338151,
        .99999986068828287678,
        -.99999996986230482845,
        .99999999412319859549,
        -.99999999897537734890,
        .99999999984183784058,
        -.99999999997864739190,
        .99999999999751767484,
        -.99999999999975652196,
        .99999999999998040668,
        -.99999999999999875788,
        .99999999999999994183,
        -.99999999999999999821,
        .99999999999999999997
      };

      Z f{};
      auto j = inc(63*k);
      for(size_t i=0; i < cm.size(); ++i, j -= k)
      {
        f += cm[i]*pow(j, -z);
      }
      if (eve::none(reflect)) return f;
      auto reflection = [&](auto f){
        if (k == 1)
        {
          auto u = dec(exp2(z));
          auto t = -2*u/dec(u)/pow(eve::pi(eve::as(real(z))), z);;
          auto g = t*cospi(eve::half(eve::as(real(z)))*z)*tgamma(z)*f;
          g = if_else(iszero, complex(eve::half(eve::as(real(f)))), g);
          return if_else(iseven, complex(eve::zero(eve::as(real(f)))), g);
        }
        else if (k == 2){
          auto g= pow(eve::two_o_pi(eve::as(real(f))), z)*sinpi(z)*tgamma(z)*f;
          return if_else(isodd, eve::zero(eve::as(real(f))), g);
        }
        else
        {
          return complex(eve::allbits(eve::as(real(f))));
        }
      };
      return if_else(reflect, reflection(f), f);
    }
    else
    {
      return cayley_extend_rev(deta, kk, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : eta
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::eta>, Z const& z) noexcept
  {
    return deta(1u, z);
  }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : zeta
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::zeta>, Z const& z) noexcept
  {
   if constexpr(concepts::complex<Z> )
    {
      auto zz=exp2(z);
      auto k = zz/(zz-2);
      auto g = if_else(z == Z(1), complex(eve::nan(eve::as(real(z)))), k*eta(z));
      return if_else(real(z) == eve::inf(eve::as(real(z))), complex(eve::one(eve::as(real(z)))), g);
    }
    else
    {
      return cayley_extend(zeta, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : lambda
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::lambda>, Z const& z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto zz=exp2(z);
      auto k = (z-1)/(z-2);
      auto r = if_else(z == complex(eve::one(eve::as(real(z)))), complex(eve::inf(eve::as(real(z)))), k*deta(1u, zz));
      imag(r) = eve::if_else(is_real(z), eve::zero, imag(r));
      return r;
    }
    else
    {
      return cayley_extend(cosh, z);
    }
  }
}

#include <kyosu/types/impl/faddeeva.hpp>
#include <kyosu/types/impl/erf.hpp>

namespace kyosu::_
{
  template<typename Z>
  EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::erfcx>, Z const& z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto realz = is_real(z);
      if (eve::all(realz))
        return complex(eve::erfcx(real(z)));
      else  if (eve::none(realz))
        return faddeeva(complex(-imag(z), real(z)));
      else
        return if_else(realz, complex(eve::erfcx(real(z))), faddeeva(complex(-imag(z), real(z))));
    }
    else
    {
      return cayley_extend(erfcx, z);
    }
  }

  template<typename Z>
  EVE_FORCEINLINE auto dispatch(eve::tag_of<kyosu::erfi>, Z const& z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto realz = is_real(z);
      if (eve::all(realz))
      {
        return kyosu::erfi(real(z));
      }
      else
      {
        auto [rz, iz] = z;
        auto tmp = erf(complex(-iz, rz));
        return complex(imag(tmp), -real(tmp));
      }
    }
    else
    {
      return cayley_extend(erfi, z);
    }
  }
}
