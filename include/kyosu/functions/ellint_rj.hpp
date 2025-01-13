//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/functions/sqrt.hpp>
#include <kyosu/functions/fma.hpp>
#include <kyosu/functions/fnma.hpp>

namespace kyosu
{

  template<typename Options>
  struct ellint_rf_t : eve::elementwise_callable<ellint_rf_t, Options, eve::threshold_option>
  {
    template<eve::floating_value T0, eve::floating_value T1,
             eve::floating_value T2, eve::floating_value T3>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c, T3 d const noexcept
    { return eve::ellint_rf(a, b, c, d); }

    template<concepts::complex T0, concepts::complex T1, concepts::complex T2, concepts::complex T3>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c, T3 d) const noexcept
    requires(concepts::complex<T0> || concepts::complex<T1> || concepts::complex<T2>|| concepts::complex<T3>)
    { return KYOSU_CALL(a, b, c, d); }

    KYOSU_CALLABLE_OBJECT(ellint_rj_t, ellint_rj_);
  };

namespace eve
{
  template<typename Options>
  struct ellint_rj_t : eve::elementwise_callable<ellint_rj_t, Options, raw_option>
  {
    template<eve::floating_value T0, eve::floating_value T1,
             eve::floating_value T2, eve::floating_value T3>
    requires (same_lanes_or_scalar<T0, T1, T2, T3>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1, T2, T3> operator()(T0 a, T1 b, T2 c, T3 d) const noexcept
    { return EVE_DISPATCH_CALL(a, b, c, d); }

    EVE_CALLABLE_OBJECT(ellint_rj_t, ellint_rj_);
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
//!      constexpr auto ellint_rj(floating_value auto x, floating_value auto y,
//!                               floating_value auto z, floating_value auto p)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ellint_rj[conditional_expr auto c](floating_value auto x, floating_value auto y,
//!                                                        floating_value auto z, floating_value auto p) noexcept; // 2
//!      constexpr auto ellint_rj[logical_value auto m](floating_value auto x, floating_value auto y,
//!                                                     floating_value auto z, floating_value auto p)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`: [floating real arguments](@ref eve::floating_value). `x`, `y` and  `z`
//!                     must be non negative and at most one of them equal to 0. In any other case,
//!                     the result is `NaN`.
//!     * `p`:  Non-zero [floating real arguments](@ref eve::floating_value). In any other case,
//!             the result is `NaN`.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. the value of the \f$\mathbf{R}_\mathbf{J}\f$ Carlson elliptic integral:
//!        \f$ \frac32 \int_{0}^{\infty}
//!        \scriptstyle(t+p)^{-1}[(t+x)(t+y)(t+z)]^{-1/2}\;\mathrm{d}t\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_rj.cpp}
//================================================================================================
  inline constexpr auto ellint_rj = functor<ellint_rj_t>;
//================================================================================================
//! @}

namespace kyosu::_
{
  template<typename T, eve::callable_options O >
  constexpr auto ellint_rf_(KYOSU_DELAY(), O const& o, T x, T y, T z, T p) noexcept
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
    auto q     = eve::pow_abs(eps(as<T>())/4, -r_t(1)/8)*kyosu::maxabs(an - x, an - y, an - z, an - p);
    
    r_t fmn(one(as(x))); // 4^-n
    r_t rc_sum(zero(as(x)));
    
    for( unsigned n = 0; n < 30; ++n )
    {
      auto rx = kyosu::sqrt(xn);
      auto ry = kyosu::sqrt(yn);
      auto rz = kyosu::sqrt(zn);
      auto rp = kyosu::sqrt(pn);
      rxn = if_else(eve::is_ltz(real(rx)), -rx, rx);
      ryn = if_else(eve::is_ltz(real(ry)), -ry, ry);
      rzn = if_else(eve::is_ltz(real(rz)), -rz, rz);
      rpn = if_else(eve::is_ltz(real(rp)), -rp, rp);
      auto dn = (rp + rx) * (rp + ry) * (rp + rz);
      auto en = delta / dn;
      en /= dn;
      auto lambda = fma(rx, ry, fma(rx, rz, ry * rz));
      auto rc1p = [](auto y_){
        auto r       = zero(as(y_));
        auto notdone = true_(as(y_)); //!= mone(as(y_));
        if( eve::any(notdone) )
        {
          auto br_yltm1 = [](auto my) { return rsqrt(my) * ellint_rc(my, dec(my)); };
          notdone       = next_interval(br_yltm1, notdone, y_ < mone(as(y_)), r, -y_);
          if( eve::any(notdone) )
          {
            auto br_ygt0 = [](auto yb){ return atan(sqrt(yb)) * rsqrt(yb);};
            notdone = next_interval(br_ygt0, notdone, is_gtz(y_), r, y_);
            if( eve::any(notdone) )
            {
              auto arg       = sqrt(-y_);
              auto log1parg  = log1p(arg);
              auto br_ygtmhf = [arg, log1parg]()
                { return if_else(is_eqz(arg), T(1), (log1parg - log1p(-arg)) / (2 * arg)); };
              notdone = next_interval(br_ygtmhf, notdone, y_ > T(-0.5), r);
              if( eve::any(notdone) )
              {
                auto br_last = [arg, log1parg](auto yy_) { return log1parg * rsqrt(inc(yy_)) / arg; };
                last_interval(br_last, notdone, r, y_);
              }
            }
          }
        }
        return r;
      };
      
      if( eve::any(test) )
      {
        //
        // occationally en ~ -1, we then have no means of calculating
        // rc(1, 1+en) without terrible cancellation error, so we
        // need to get to 1+en directly.  by substitution we have
        //
        // 1+e_0 = 1 + (p-x)*(p-y)*(p-z)/((sqrt(p) + sqrt(x))*(sqrt(p)+sqrt(y))*(sqrt(p)+sqrt(z)))^2
        //       = 2*sqrt(p)*(p+sqrt(x) * (sqrt(y)+sqrt(z)) + sqrt(y)*sqrt(z)) / ((sqrt(p) +
        //       sqrt(x))*(sqrt(p) + sqrt(y)*(sqrt(p)+sqrt(z))))
        //
        // and since this is just an application of the duplication formula for rj, the same
        // expression works for 1+en if we use x,y,z,p_n etc.
        // this branch is taken only once or twice at the start of iteration,
        // after than en reverts to it's usual very small values.
        //
        auto b   = 2 * rp * (pn + rx * (ry + rz) + ry * rz) / dn;
        auto r0  = ellint_rc(T(1), b);
        auto r1  = rc1p(en);
        auto tmp = if_else(test, r0, r1);
        rc_sum += fmn / dn * tmp;
      }
      else
      {
        auto r = rc1p(en);
        rc_sum += fmn / dn * r;
      }
      
      // from here on we move to n+1:
      an = (an + lambda) * r_t(0.25); // / 4;
      fmn /= 4;
      
      if( eve::all(fmn * q < kyosu::abs(an)) ) break;
      
      xn = (xn + lambda) * T(0.25); // / 4;
      yn = (yn + lambda) * T(0.25); // / 4;
      zn = (zn + lambda) * T(0.25); // / 4;
      pn = (pn + lambda) * T(0.25); // / 4;
      delta *= T(0.015625);         // /= 64;
    }
    auto fmninvan = fmn * rec[pedantic](an);
    auto xx       = (a0 - x) * fmninvan;
    auto yy       = (a0 - y) * fmninvan;
    auto zz       = (a0 - z) * fmninvan;
    p             = -(xx + yy + zz) / 2;
    auto p2       = sqr(p);
    auto xxyy     = xx * yy;
    auto e2       = xxyy + fma(xx, zz, fms(yy, zz, 3 * p2));
    auto p3       = p * p2;
    auto xxyyzz   = xxyy * zz;
    auto e3       = xxyyzz + 2 * e2 * p + 4 * p3;
    auto e4       = (2 * xxyyzz + e2 * p + 3 * p3) * p;
    auto e5       = xxyyzz * p2;
    auto e22      = sqr(e2);
    auto result   = fmninvan * rsqrt(an)
      * (1 - 3 * e2 / 14 + e3 / 6 + 9 * e22 / 88 - 3 * e4 / 22 - 9 * e2 * e3 / 52
         + 3 * e5 / 26 - e2 * e22 / 16 + 3 * e3 * e3 / 40 + 3 * e2 * e4 / 20
         + 45 * e22 * e3 / 272 - 9 * (e3 * e4 + e2 * e5) / 68);
    
    result += 6 * rc_sum;
    return result;
  }
}
