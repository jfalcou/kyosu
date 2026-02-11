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
#include <kyosu/constants/wrapped.hpp>
#include <eve/module/special/regular/tgamma.hpp>

namespace kyosu
{
  template<typename Options> struct tgamma_inv_t : eve::elementwise_callable<tgamma_inv_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(tgamma_inv_t, tgamma_inv_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var tgamma_inv
  //!   @brief Computes \f$\frac1{\Gamma(z)}\f$.
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
  //!      constexpr auto tgamma_inv(cayley_dickson_like auto z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z` : Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns  \f$\frac1{\Gamma(z)}\f$.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Gamma Function](https://mathworld.wolfram.com/GammaFunction.html)
  //!   *  [Wikipedia: Gamma function](https://en.wikipedia.org/wiki/Gamma_function)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/tgamma_inv.cpp}
  //======================================================================================================================
  inline constexpr auto tgamma_inv = eve::functor<tgamma_inv_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O> constexpr auto tgamma_inv_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>)
    {
      return if_else(eve::is_flint(z) && eve::is_lez(z), eve::zero(as(z)) * eve::sign_alternate(z),
                     eve::rec[eve::pedantic](eve::tgamma(z)));
    }
    else if constexpr (concepts::complex<Z>)
    {
      using u_t = eve::underlying_type_t<Z>;
      constexpr auto hf = eve::half(eve::as<u_t>());

      auto br_gthf = [](auto z) {
        u_t log_sqrt_2Pi = 0.91893853320467274177;
        u_t g = 4.7421875;
        Z z_m_0p5 = z - 0.5;
        Z z_pg_m0p5 = z_m_0p5 + g;
        Z zm1 = z - 1.0;
        u_t const c[15] = {0.99999999999999709182,     57.156235665862923517,      -59.597960355475491248,
                           14.136097974741747174,      -0.49191381609762019978,    0.33994649984811888699E-4,
                           0.46523628927048575665E-4,  -0.98374475304879564677E-4, 0.15808870322491248884E-3,
                           -0.21026444172410488319E-3, 0.21743961811521264320E-3,  -0.16431810653676389022E-3,
                           0.84418223983852743293E-4,  -0.26190838401581408670E-4, 0.36899182659531622704E-5};

        Z sum(c[0]);
        for (int i = 1; i < 15; ++i) sum += c[i] / (zm1 + i);
        return kyosu::exp(z_pg_m0p5 - z_m_0p5 * kyosu::log(z_pg_m0p5) - log_sqrt_2Pi) / sum;
      };

      auto br_lehf = [br_gthf](auto z) {
        auto x = real(z);
        auto n = eve::nearest(x);
        auto eps = z - n;
        auto r = kyosu::sinpi(eps) * eve::inv_pi(as<u_t>()) / br_gthf(kyosu::oneminus(z));
        return kyosu::if_else(eve::is_even(n), r, -r);
      };

      auto r = kyosu::nan(as<Z>());
      auto notdone = is_nan(r);
      if (eve::any(notdone))
      {
        notdone = next_interval(br_gthf, notdone, real(z) > hf, r, z);
        if (eve::any(notdone)) { last_interval(br_lehf, notdone, r, z); }
      }
      return r;
    }
    else { return cayley_extend(tgamma_inv, z); }
  }
}
