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
  struct ellint_rd_t : eve::elementwise_callable<ellint_rd_t, Options, eve::threshold_option>
  {
    template<eve::floating_value T0, eve::floating_value T1,
             eve::floating_value T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c) const noexcept
    { return eve::ellint_rd(a, b, c); }

    template<concepts::complex T0, concepts::complex T1, concepts::complex T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c) const noexcept
    requires(concepts::complex<T0> || concepts::complex<T1> || concepts::complex<T2>)
    { return KYOSU_CALL(a, b, c); }

    KYOSU_CALLABLE_OBJECT(ellint_rd_t, ellint_rd_);
  };

//================================================================================================
//! @addtogroup functions
//! @{
//!   @var ellint_rd
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
//!      constexpr auto ellint_rd(floating_value auto x, floating_value auto y,
//!                               floating_value auto z)                          noexcept; // 1
//!
//!      // semantic modifier
//!      constexpr auto ellint_rd[threshold = tol](floating_value auto x, floating_value auto y,
//!                                                floating_value auto z)         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ellint_rd[conditional_expr auto c](floating_value auto x, floating_value auto y,
//!                                                        floating_value auto z) noexcept; // 2
//!      constexpr auto ellint_rd[logical_value auto m](floating_value auto x, floating_value auto y,
//!                                                     floating_value auto z)    noexcept; // 2
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
//!        (default to `eps(as<T>())`),  under one of these condition:
//!        -  `x`, `y` and  `z` must have nonnegative real part and at most one
//!            of them be 0, while `real(p) > 0`.
//!        -  if `p` ìs not 0 and \f$|arg(p)| < \pi\f$, either `x`, `y` and  `z` real and nonnegative and at most one of them be 0,
//!        -  two of the variables `x`, `y` and  `z` nonzero and conjugate complex with phase less in magnitude than  \f$\pi\f$ and the
//!           third variable be real and nonnegative.
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_rd.cpp}
//================================================================================================
  inline constexpr auto ellint_rd = eve::functor<ellint_rd_t>;
//================================================================================================
//! @}
}
namespace kyosu::_
{
  template<typename T, eve::callable_options O >
  constexpr auto ellint_rd_(KYOSU_DELAY(), O const& o, T x, T y, T z) noexcept
  {
    using r_t = eve::underlying_type_t<T>;
    constexpr r_t  hf  = half(as<r_t>());
    constexpr r_t  qtr = r_t(0.25);
    auto tol = [&](){
      if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(x);
      else return eve::eps(eve::as(real(x)));
    }();
    auto xn    = x;
    auto yn    = y;
    auto zn    = z;
    auto pn    = p;

    auto an     = kyosu::average(x, y, z, z, z);
    auto a0     = an;
    auto epsi   = eve::pow_abs(qtr*tol, -eve::rec(r_t(6)));
    auto q = epsi *kyosu::maxabs(an - x, an - y, an - z)*r_t(1.2);
    r_t fn(one(as<r_t>()));
    auto rd_sum(zero(as(x)));

    // duplication
    for(unsigned k  = 0 ; k < 30; ++k )
    {
      T rx = kyosu::sqrt(xn);
      T ry = kyosu::sqrt(yn);
      T rz = kyosu::sqrt(zn);
      rx = if_else(eve::is_ltz(real(rx)), -rx, rx);
      ry = if_else(eve::is_ltz(real(ry)), -ry, ry);
      rz = if_else(eve::is_ltz(real(rz)), -rz, rz);
      T lambda = rx * ry + rx * rz + ry * rz;
      rd_sum += fn / (rz * (zn + lambda));
      an = average(an, lambda) * hf;
      xn = average(xn, lambda) * hf;
      yn = average(yn, lambda) * hf;
      zn = average(zn, lambda) * hf;
      q *= qtr;
      fn *= qtr;
      if( eve::all(q < kyosu::abs(an)) ) break;
    }

    T invan = rec[pedantic](an);
    T xx    = fn*(a0 - x)*invan;
    T yy    = fn*(a0 - y)*invan;
    T zz    = -(xx + yy)/3;
    T xxyy  = xx*yy;
    T zz2   = sqr(zz);
    T e2    = fnma(T(6), zz2, xxyy);
    T e3    = (3*xxyy - 8*zz2)*zz;
    T e4    = 3*(xxyy - zz2)*zz2;
    T e5    = xxyy*zz2*zz;

    constexpr elt_t c0  = r_t(-3 / 14.0);
    constexpr elt_t c1  = r_t(1 / 6.0);
    constexpr elt_t c2  = r_t(9 / 88.0);
    constexpr elt_t c3  = r_t(-3 / 22.0);
    constexpr elt_t c4  = r_t(-9 / 52.0);
    constexpr elt_t c5  = r_t(3 / 26.0);
    constexpr elt_t c6  = r_t(-1 / 16.0);
    constexpr elt_t c7  = r_t(3 / 40.0);
    constexpr elt_t c8  = r_t(3 / 20.0);
    constexpr elt_t c9  = r_t(45 / 272.0);
    constexpr elt_t c10 = r_t(-9 / 68.0);

    T e22    = sqr(e2);
    T result = fn*invan*sqrt(invan)
      *(1 + e2*c0 + e3*c1 + e22*c2 + e4*c3 + e2*(e3*c4 + e22*c6) + e5*c5
        + sqr(e3)*c7 + e2*e4*c8 + c9*e22*e3 + (e3*e4 + e2*e5)*c10);

    return r_t(3)*rd_sum+result);
  }
}
