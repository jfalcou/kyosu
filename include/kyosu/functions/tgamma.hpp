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
  struct tgamma_t : eve::elementwise_callable<tgamma_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::tgamma(v); }

    KYOSU_CALLABLE_OBJECT(tgamma_t, tgamma_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tgamma
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
//!     Returns \f$\Gamma(z)\f$.
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
  constexpr auto tgamma_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using r_t = eve::element_type_t<as_real_type_t<Z>>;
//      auto  g=r_t(607)/r_t(128);
      using u_t = eve::underlying_type_t<Z>;
      constexpr auto hf = eve::half(eve::as<u_t>());

      auto br_gthf = [](auto z){
        u_t log_sqrt_2Pi = 0.91893853320467274177;
        u_t g = 4.7421875;
        Z z_m_0p5 = z - 0.5;
        Z z_pg_m0p5 = z_m_0p5 + g;
        Z zm1 = z - 1.0;
        const u_t c[15] = {0.99999999999999709182,
                           57.156235665862923517,
                           -59.597960355475491248,
                           14.136097974741747174,
                           -0.49191381609762019978,
                           0.33994649984811888699E-4,
                           0.46523628927048575665E-4,
                           -0.98374475304879564677E-4,
                           0.15808870322491248884E-3,
                           -0.21026444172410488319E-3,
                           0.21743961811521264320E-3,
                           -0.16431810653676389022E-3,
                           0.84418223983852743293E-4,
                           -0.26190838401581408670E-4,
                           0.36899182659531622704E-5};

        Z sum(c[0]);
        for (int i = 1 ; i < 15 ; ++i) sum += c[i]/(zm1 + i);
        auto u = z_pg_m0p5 - z_m_0p5*kyosu::log(z_pg_m0p5) - log_sqrt_2Pi;
        return sum*kyosu::exp(-u);
      };

      auto br_lehf = [br_gthf](auto z){
        auto x = real(z);
        auto n = eve::nearest(x);
        auto eps = z - n;
        auto r = eve::pi(as<u_t>())/(kyosu::sinpi(eps)*br_gthf(kyosu::oneminus(z)));
        return kyosu::if_else(eve::is_even(n), r, -r);
      };

      auto r = kyosu::nan(as<Z>());
      auto notdone = is_nan(r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_gthf, notdone, real(z) > hf, r, z);
        if( eve::any(notdone) )
        {
          last_interval(br_lehf, notdone, r, z);
        }
      }
      return r;
    }
    else
    {
      return cayley_extend(tgamma, z);
    }
  }
}
