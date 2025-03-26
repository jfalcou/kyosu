//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sinpi.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/log.hpp>

namespace kyosu
{
  template<typename Options>
  struct log_gamma_t : eve::strict_elementwise_callable<log_gamma_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log_gamma
//!   @brief Computes \f$\Gamma(z)\f$r.
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
//!      constexpr T  log_gamma(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns \f$\Gamma(z)\f$.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Gamma Function](https://mathworld.wolfram.com/GammaFunction.html)
//!   *  [Wikipedia: Gamma function](https://en.wikipedia.org/wiki/Gamma_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/log_gamma.cpp}
//======================================================================================================================
  inline constexpr auto log_gamma = eve::functor<log_gamma_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto log_gamma_(KYOSU_DELAY(), O const&, Z a0) noexcept
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
}
