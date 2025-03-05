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
  struct tgamma_t : eve::elementwise_callable<tgamma_t, Options, kyosu::incomplete_option
                                              , eve::lower_option, eve::upper_option>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::tgamma(v); }

    template<concepts::cayley_dickson Z, typename T>
    KYOSU_FORCEINLINE constexpr auto operator()(Z z, T x) const noexcept
    {
      using r_t = decltype(z+x);
      return KYOSU_CALL(r_t(z), r_t(x));
    }

    template<concepts::real V, concepts::real T >
    KYOSU_FORCEINLINE constexpr V operator()(V v, T x ) const noexcept
    {
      if constexpr(Options::contains(eve::lower))
        return eve::gamma_p(v, x);
      else if constexpr(Options::contains(eve::upper))
        return eve::tgamma(v) - eve::gamma_p(v, x);
      else
        return eve::gamma_p(v, x);
    }

    KYOSU_CALLABLE_OBJECT(tgamma_t, tgamma_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tgamma
//!   @brief Computes \f$\Gamma(z)\f$, \f$\Gamma(z, x)\f$ and \f$\gamma(z, x)\f$,  the gamma function and the upper and lower
//!     incomplete gamma functions
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
//!      constexpr T  tgamma(T z) noexcept;                                                      // 1
//!      constexpr T  tgamma(T z, T x) noexcept;                                                 // 2
//!
//!      // Semantic modifyers
//!      constexpr T  tgamma[lower](T z, T x) noexcept;                                          // 2
//!      constexpr T  tgamma[upper](T z, T x) noexcept;                                          // 3
//!    é constexpr T  tgamma[normalized](/*any previous two parameters overloads*/)   noexcept;  // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     1. Returns \f$\Gamma(z)\f$.
//!     2. The value of the lower incomplete \f$\Gamma\f$ function:
//!        \f$\displaystyle \int_0^{x} t^{z-1}e^{-t}\mbox{d}t\f$ is returned.
//!     3. The value of the upper incomplete \f$\Gamma\f$ function:
//!        \f$\displaystyle \int_{x}^{\infty} t^{z-1}e^{-t}\mbox{d}t\f$ is returned.
//!     4. The value of the normalized incomplete gamma function (i.e devided by \f$Gamma(z)\f$ is returned.
//!
//!  @note the extension to the complex plane is done using the confluent hypergeometric function \f${}_1F_1\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Gamma Function](https://mathworld.wolfram.com/GammaFunction.html)
//!   *  [Wikipedia: Gamma function](https://en.wikipedia.org/wiki/Gamma_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/tgamma.cpp}
//======================================================================================================================
  inline constexpr auto tgamma = eve::functor<tgamma_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto tgamma_(KYOSU_DELAY(), O const&, Z a0) noexcept
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
        f = if_else(negra0, rec(-eve::inv_pi(eve::as(real(a0)))*a0*f*sinpi(a0)), eve::zero);
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

//#include <kyosu/details/tgamma_impl.hpp>
#include <kyosu/functions/hypergeometric.hpp>

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto tgamma_(KYOSU_DELAY(), O const&, Z a, Z x) noexcept
  {
    if constexpr(O::contains(eve::upper))
    {
      auto r = kyosu::rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)});
      if constexpr(O::contains(kyosu::regularized))
        return r*tgamma_inv(a);
      else
        return r;
    }
    else
    {
      auto r = kyosu::tgamma(a)-rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)});
      if constexpr(O::contains(kyosu::regularized))
        return kyosu::oneminus(kyosu::rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)}));
      else
        return kyosu::tgamma(a) - kyosu::rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)});
    }
  }
}
