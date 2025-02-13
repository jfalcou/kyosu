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
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }


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
  constexpr auto log_gamma_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using u_t = eve::underlying_type_t<Z>;
      constexpr auto hf = eve::half(eve::as<u_t>());

      auto br_gthf = [&](auto zz){  //real(z) > hf
        u_t log_sqrt_2Pi = 0.91893853320467274177;
        auto  g=u_t(607)/u_t(128);// 4.7421875;
        Z z_m_0p5 = zz - 0.5;
        Z z_pg_m0p5 = z_m_0p5 + g;
        Z zm1 = zz - 1.0;
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
        return log_sqrt_2Pi + kyosu::log (sum) + z_m_0p5*kyosu::log(z_pg_m0p5) - z_pg_m0p5;
      };

      auto br_ypos = [&](auto zz){ //imag(z) > 0
        auto [x, y] = zz;
        auto n =  eve::nearest(x);
        n = if_else( x <  n, eve::dec(n), n);
        auto log_Pi = u_t(1.1447298858494002);
        auto log_const(kyosu::complex(-eve::log_2(eve::as<u_t>()), eve::pio_2(eve::as<u_t>())));
        auto i_Pi(kyosu::complex(u_t(0.0),eve::pi(eve::as<u_t>())));
        auto eps = z - n;
        auto log_sin_Pi_z = if_else(y > 110, -i_Pi*z + log_const, kyosu::log(kyosu::sinpi(eps)) - i_Pi*n);
        auto r = log_Pi - log_sin_Pi_z - log_gamma(kyosu::oneminus(zz));
        return r;
      };

      auto r = kyosu::nan(as<Z>());
      auto notdone = is_nan(r);
      auto [x, y] = z;
      auto ypos = eve::is_gtz(y);
      imag(z) = eve::abs(y);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_gthf, notdone, x >= hf, r, z);
        if( eve::any(notdone) )
        {
          last_interval(br_ypos, notdone, r, z);
        }
      }
      r = kyosu::if_else(ypos, r, conj(r));
      return r;
    }
    else
    {
      return cayley_extend(log_gamma, z);
    }
  }
}
