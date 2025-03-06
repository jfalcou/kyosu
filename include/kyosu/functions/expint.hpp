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
  struct expint_t : eve::elementwise_callable<expint_t, Options, kyosu::incomplete_option
                                              , eve::lower_option, eve::upper_option>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::expint(v); }

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
        return eve::expint(v) - eve::gamma_p(v, x);
      else
        return eve::gamma_p(v, x);
    }

    KYOSU_CALLABLE_OBJECT(expint_t, expint_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp_int
//!   @brief  `elementwise_callable` object computing the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto exp_int(concepts::cayley_dickson auto x)                                   noexcept; // 1
//!      constexpr auto exp_int(concepts::cayley_dickson auto n, floating_value auto x)            noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: order. If not present taken to be 1.
//!     * `x`: cayley_dickson or real argument.
//!
//!   **Return value**
//!
//!     1. The value of the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$, is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld:Exponential Integral ](https://mathworld.wolfram.com/ExponentialIntegral.html)
//!   *  [DLMF: Generalized Exponential Integral](https://dlmf.nist.gov/8.19#i)
//!   *  [Wikipedia: Exponential integral](https://en.wikipedia.org/wiki/Exponential_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/exp_int.cpp}
//======================================================================================================================
  inline constexpr auto expint = eve::functor<expint_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto expint_(KYOSU_DELAY(), O const&, Z a0) noexcept
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
      f = if_else (reala0, complex(eve::expint(real(a0))), f);
      f = if_else (eve::is_nan(real(f)), complex(eve::nan(eve::as(sq2pi)), eve::inf(eve::as(sq2pi))), f);
      f = if_else (is_eqz(a0), complex(eve::inf(eve::as(g))*eve::signnz[eve::pedantic](real(a0))), f);
      return f;
    }
    else
    {
      return cayley_extend(expint, a0);
    }
  }
}

#include <kyosu/details/expint_impl.hpp>
#include <kyosu/functions/hypergeometric.hpp>

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr auto expint_(KYOSU_DELAY(), O const&, Z a, Z x) noexcept
  {
    if constexpr(O::contains(eve::upper))
    {
      auto r = kyosu::rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)});
      if constexpr(O::contains(kyosu::regularized))
        return r*expint_inv(a);
      else
        return r;
    }
    else
    {
      auto r = kyosu::expint(a)-rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)});
      if constexpr(O::contains(kyosu::regularized))
        return kyosu::oneminus(kyosu::rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)}));
      else
        return kyosu::expint(a) - kyosu::rec(a)*kyosu::pow(x, a)*kyosu::hypergeometric(-x, kumi::tuple{a}, kumi::tuple{inc(a)});
    }
  }
}
//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <kyosu/functions/tricomi.hpp>

namespace kyosu
{
  template<typename Options>
  struct expint_t : strict_elementwise_callable<expint_t, Options, saturated_option>
  {
    template<typename Z, typename N>
    constexpr KYOSU_FORCEINLINE
    auto operator()(N n, Z x) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(n, kyosu::complex(z));
      else
      {
        using r_t = decltype(z+n);
        return kyosu::tricomi(n, n, x);
      }

    template<typename Z>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    {
      return kyosu::tricomi(1, 1, x);
    }

    EVE_CALLABLE_OBJECT(expint_t, expint_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var expint
//!   @brief  `elementwise_callable` object computing the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto expint(floating_value auto x)                                   noexcept; // 1
//!      constexpr auto expint(unsigned_value auto n, floating_value auto x)            noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto expint[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
//!      constexpr auto expint[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: [unsigned argument](@ref eve::unsigned_value). If not present taken to be 1.
//!     * `x`: [real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$, is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld:Exponential Integral ](https://mathworld.wolfram.com/ExponentialIntegral.html)
//!   *  [DLMF: Generalized Exponential Integral](https://dlmf.nist.gov/8.19#i)
//!   *  [Wikipedia: Exponential integral](https://en.wikipedia.org/wiki/Exponential_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/expint.cpp}
//================================================================================================
  inline constexpr auto expint = functor<expint_t>;
//================================================================================================
//! @}
//================================================================================================
