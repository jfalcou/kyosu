//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct log_gamma_t : eve::elementwise_callable<log_gamma_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log_gamma
//!   @brief Computes the log of the \f$\Gamma\f$ function.
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
//!      constexpr auto  log_gamma(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns \f$\log(\Gamma(z))\f$. If z is floating the result is as if `complex(z)` was used in the call.
//!
//!  @groupheader{Example}
//!
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
  KYOSU_FORCEINLINE constexpr Z log_gamma_(KYOSU_DELAY(), O const&, Z a0) noexcept
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
