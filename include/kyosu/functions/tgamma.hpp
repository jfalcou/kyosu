//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/dec.hpp>
#include <kyosu/functions/is_flint.hpp>
#include <kyosu/functions/nearest.hpp>
#include <kyosu/functions/sinpi.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/details/decorators.hpp>

namespace kyosu
{
  template<typename Options>
  struct tgamma_t : eve::elementwise_callable<tgamma_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    KYOSU_CALLABLE_OBJECT(tgamma_t, tgamma_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tgamma
//!   @brief Computes \f$\Gamma(z)\f$ the gamma function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      // regular calls
//!      constexpr T  tgamma(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     returns \f$\Gamma(z)\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Gamma Function](https://mathworld.wolfram.com/GammaFunction.html)
//!   *  [Wikipedia: Gamma function](https://en.wikipedia.org/wiki/Gamma_function)
//!
//!  @note Γ can be used as an alias in code.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/tgamma.cpp}
//======================================================================================================================
  inline constexpr auto tgamma = eve::functor<tgamma_t>;
  inline constexpr auto Γ = eve::functor<tgamma_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto tgamma_(KYOSU_DELAY(), O const&, Z a0) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::tgamma(a0);
    else if constexpr(concepts::complex<Z> )
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
      z = kyosu::dec(z);
      auto zh = z+eve::half(eve::as<r_t>());
      auto zgh=zh+g;
      //trick for avoiding FP overflow above z=141
      auto zp=kyosu::pow(zgh,(zh*eve::half(eve::as<r_t>())));
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
        f = if_else(negra0, rec(-eve::inv_pi(eve::as(real(a0)))*a0*f*sinpi(a0)), f);
        f = if_else (negra0 && reala0 && eve::is_flint(real(a0)), complex(eve::nan(eve::as(sq2pi)), eve::inf(eve::as(sq2pi))), f);
     }
      f = if_else (reala0, complex(eve::tgamma(real(a0))), f);
      f = if_else (eve::is_nan(real(f)), complex(eve::nan(eve::as(sq2pi)), eve::inf(eve::as(sq2pi))), f);
      f = if_else (is_eqz(a0), complex(eve::inf(eve::as(g))*eve::signnz[eve::pedantic](real(a0))), f);
      return f;
    }
    else
    {
      return cayley_extend(tgamma, a0);
    }
  }
}
