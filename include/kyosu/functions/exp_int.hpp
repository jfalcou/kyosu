//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/fnan.hpp>
#include <kyosu/constants/cinf.hpp>
#include <kyosu/functions/digamma.hpp>
#include <kyosu/functions/is_not_nan.hpp>
#include <kyosu/functions/is_nez.hpp>
#include <kyosu/functions/is_eqz.hpp>
#include <kyosu/functions/linfnorm.hpp>
#include <kyosu/functions/tgamma_inv.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/hypergeometric.hpp>

namespace kyosu
{
  template<typename Options> struct exp_int_t : eve::elementwise_callable<exp_int_t, Options>
  {
    template<concepts::cayley_dickson_like N, concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::common_value_t<Z, N> operator()(N const& n, Z const& z) const noexcept
    {
      return KYOSU_CALL(n, z);
    }

    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(Z(1), z);
    }

    KYOSU_CALLABLE_OBJECT(exp_int_t, exp_int_);
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
  //!     * `n`: order. cayley_dickson or real argument. If not present taken to be 1.
  //!     * `x`: cayley_dickson or real argument.
  //!
  //!   **Return value**
  //!
  //!     1. The value of the exponential integral \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$, is returned.
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
  inline constexpr auto exp_int = eve::functor<exp_int_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr eve::common_value_t<Z, N> exp_int_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
    using r_t = eve::common_value_t<Z, N>;
    using u_t = eve::underlying_type_t<r_t>;
    if constexpr (concepts::real<Z> && concepts::real<N>) return eve::exp_int(n, z);
    else
    {
      auto r = kyosu::fnan(kyosu::as<r_t>());
      r = if_else(kyosu::is_eqz(z), kyosu::cinf(as(z)), r);
      auto notdone = kyosu::is_not_nan(z) && kyosu::is_nez(z);

      auto br_small = [](auto nn, auto zz) { // |z| < thresh
        constexpr auto tol = eve::eps(eve::as<u_t>());
        auto mzz = -zz;
        auto dn = dec(nn);
        auto s = kyosu::zero(eve::as(zz));
        auto isflint = kyosu::is_flint(kyosu::real(nn));
        if (eve::all(isflint))
          s = kyosu::tgamma_inv(nn) * kyosu::pow(mzz, dec(nn)) * (kyosu::digamma(nn) - kyosu::log(zz));
        else if (eve::none(isflint)) s = kyosu::tgamma(-dn) * pow(zz, dn);
        else
        {
          auto sflint = kyosu::tgamma_inv(nn) * kyosu::pow(mzz, dec(nn)) * (kyosu::digamma(nn) - kyosu::log(zz));
          auto sfloat = kyosu::tgamma(-dn) * pow(zz, dn);
          s = kyosu::if_else(kyosu::is_flint(nn), sflint, sfloat);
        }
        auto test = kyosu::false_(eve::as(zz));
        auto fac = kyosu::one(eve::as(zz));

        s -= kyosu::if_else(kyosu::is_eqz(dn), zero, -fac / dn);
        constexpr int Maxit = 500;
        for (size_t k = 1; k <= Maxit; ++k)
        {
          fac *= zz * kyosu::mone(eve::as(zz)) / k;
          auto t = fac / (k - dn);
          s -= if_else(is_nez(k - dn), t, zero);
          test = kyosu::linfnorm[kyosu::flat](t) <= kyosu::linfnorm[kyosu::flat](s) * tol;
          if (eve::all(test)) { return s; }
        };
        return kyosu::fnan(as(s));
      };

      auto br_large = [](auto nn, auto zz) { // |z| >=thresh
        return kyosu::exp(-zz) / zz;
      };

      u_t constexpr thresh = 18.0;
      if (eve::any(notdone))
      {
        notdone = next_interval(br_small, notdone, kyosu::abs(kyosu::real(z)) < thresh, r, n, z);
        if (eve::any(notdone)) { last_interval(br_large, notdone, r, n, z); }
      }
      return r;
    }
  }
}
