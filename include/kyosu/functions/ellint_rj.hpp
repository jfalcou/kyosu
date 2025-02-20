//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/elliptic/ellint_rj.hpp>
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/functions/sqrt.hpp>
#include <kyosu/functions/fma.hpp>
#include <kyosu/functions/fms.hpp>

namespace kyosu
{

  template<typename Options>
  struct ellint_rj_t : eve::elementwise_callable<ellint_rj_t, Options, eve::threshold_option>
  {
    template<eve::floating_value T0, eve::floating_value T1,
             eve::floating_value T2, eve::floating_value T3>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c, T3 d) const noexcept
    { return eve::ellint_rj(a, b, c, d); }

    template<concepts::complex T0, concepts::complex T1, concepts::complex T2, concepts::complex T3>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c, T3 d) const noexcept
    requires(concepts::complex<T0> || concepts::complex<T1> || concepts::complex<T2>|| concepts::complex<T3>)
    { return KYOSU_CALL(a, b, c, d); }

    KYOSU_CALLABLE_OBJECT(ellint_rj_t, ellint_rj_);
  };

//================================================================================================
//! @addtogroup functions
//! @{
//!   @var ellint_rj
//!   @brief Computes the Carlson's elliptic integral
//!   \f$ \mathbf{R}_\mathbf{J}(x, y) = \frac32 \int_{0}^{\infty}
//!   \scriptstyle(t+p)^{-1}[(t+x)(t+y)(t+z)]^{-1/2}\scriptstyle\;\mathrm{d}t\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto ellint_rj(auto x, auto y, auto z, auto p)                          noexcept; // 1
//!
//!      // semantic modifier
//!      constexpr auto ellint_rj[threshold = tol](auto x, auto y, auto z, auto p)         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ellint_rj[conditional_expr auto c](auto x, auto y, auto z, auto p) noexcept; // 2
//!      constexpr auto ellint_rj[logical_value auto m](auto x, auto y, auto z, auto p)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`: [floating real arguments](@ref eve::floating_value).
//!     * `p`:  [floating real arguments](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. the value of the \f$\mathbf{R}_\mathbf{J}\f$ Carlson elliptic integral:
//!        \f$ \frac32 \int_{0}^{\infty}
//!        \scriptstyle(t+p)^{-1}[(t+x)(t+y)(t+z)]^{-1/2}\;\mathrm{d}t\f$ is returned with relative error less in magnitude than tol
//!        (default to [eps](@ref eve::eps)),
//!        The integral is well defined if `x`, `y`, `z` lie in the
//!        complex plane cut along the nonpositive real axis,
//!        with the exception that at at most one of `x`, `y`, `z` can be 0.
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/ellint_rj.cpp}
//================================================================================================
  inline constexpr auto ellint_rj = eve::functor<ellint_rj_t>;
//================================================================================================
//! @}
}
namespace kyosu::_
{
  template<typename T, eve::callable_options O >
  constexpr auto ellint_rj_(KYOSU_DELAY(), O const& o, T x, T y, T z, T p) noexcept
  {
    using r_t = eve::underlying_type_t<T>;
    auto tol = [&](){
      if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(x);
      else return eve::eps(eve::as(real(x)));
    }();
    auto xn    = x;
    auto yn    = y;
    auto zn    = z;
    auto pn    = p;

    auto an    = kyosu::average(x, y, z, p, p);
    auto a0    = an;
    auto delta = (p - x) * (p - y) * (p - z);
    auto q     = eve::pow_abs(tol/4, -r_t(1)/8)*kyosu::maxabs(an - x, an - y, an - z, an - p);

    r_t fmn(one(as<r_t>())); // 4^-n
    auto rc_sum(zero(as(x)));

    for( unsigned n = 0; n < 30; ++n )
    {
      auto rx = kyosu::sqrt(xn);
      auto ry = kyosu::sqrt(yn);
      auto rz = kyosu::sqrt(zn);
      auto rp = kyosu::sqrt(pn);
      rx = if_else(eve::is_ltz(real(rx)), -rx, rx);
      ry = if_else(eve::is_ltz(real(ry)), -ry, ry);
      rz = if_else(eve::is_ltz(real(rz)), -rz, rz);
      rp = if_else(eve::is_ltz(real(rp)), -rp, rp);
      auto dn = (rp + rx) * (rp + ry) * (rp + rz);
      auto en = delta / dn;
      en /= dn;
      auto lambda = fma(rx, ry, fma(rx, rz, ry * rz));
      rc_sum += fmn / dn * ellint_rc(T(1), inc(en));

      an = (an + lambda) * r_t(0.25); // / 4;
      fmn /= 4;

      if( eve::all(fmn * q < kyosu::abs(an)) ) break;

      xn = (xn + lambda) * T(0.25); // / 4;
      yn = (yn + lambda) * T(0.25); // / 4;
      zn = (zn + lambda) * T(0.25); // / 4;
      pn = (pn + lambda) * T(0.25); // / 4;
      delta *= T(0.015625);         // /= 64;
    }
    auto fmninvan = fmn * kyosu::rec(an);
    auto xx       = (a0 - x) * fmninvan;
    auto yy       = (a0 - y) * fmninvan;
    auto zz       = (a0 - z) * fmninvan;
    p             = -(xx + yy + zz) / 2;
    auto p2       = sqr(p);
    auto xxyy     = xx * yy;
    auto e2       = xxyy + kyosu::fma(xx, zz, kyosu::fms(yy, zz, 3 * p2));
    auto p3       = p * p2;
    auto xxyyzz   = xxyy * zz;
    auto e3       = xxyyzz + 2 * e2 * p + 4 * p3;
    auto e4       = (2 * xxyyzz + e2 * p + 3 * p3) * p;
    auto e5       = xxyyzz * p2;
    auto e22      = sqr(e2);
    auto result   = fmninvan /kyosu::sqrt(an)
      * (1 - 3 * e2 / 14 + e3 / 6 + 9 * e22 / 88 - 3 * e4 / 22 - 9 * e2 * e3 / 52
         + 3 * e5 / 26 - e2 * e22 / 16 + 3 * e3 * e3 / 40 + 3 * e2 * e4 / 20
         + 45 * e22 * e3 / 272 - 9 * (e3 * e4 + e2 * e5) / 68);
    result += 6 * rc_sum;
    return result;
  }
}
