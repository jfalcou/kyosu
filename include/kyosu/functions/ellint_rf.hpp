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
    template<eve::floating_value T0, eve::floating_value T1,  eve::floating_value T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c) const noexcept
    { return eve::ellint_rf(a, b, c); }

    template<concepts::complex T0, concepts::complex T1, concepts::complex T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b, T2 c) const noexcept
    requires(concepts::complex<T0> || concepts::complex<T1> || concepts::complex<T2>)
    { return KYOSU_CALL(a, b, c); }

    KYOSU_CALLABLE_OBJECT(ellint_rf_t, ellint_rf_);
  };


//================================================================================================
//! @addtogroup functions
//! @{
//!   @var ellint_rf
//!   @brief Computes the Carlson's elliptic integral
//!   \f$  \mathbf{R}_\mathbf{F}(x, y) =
//!   \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)(t+z)]^{-1/2}\scriptstyle\;\mathrm{d}t\f$.
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
//!      constexpr auto ellint_rf(floating_value auto x, floating_value auto y, floating_value auto z)   noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ellint_rf[conditional_expr auto c](floating_value auto x, floating_value auto y,
//!                                                        floating_value auto z)                        noexcept; // 2
//!      constexpr auto ellint_rf[logical_value auto m](floating_value auto x, floating_value auto y,
//!                                                     floating_value auto z)                           noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`:  [floating values](@ref eve::floating_value).
//!                       All those arguments must be non-negative and at most one zero or the
//!                       the result is NaN.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. the value of the \f$\mathbf{R}_\mathbf{F}\f$ Carlson elliptic integral:
//!       \f$  \mathbf{R}_\mathbf{F}(x, y) =
//!       \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
//!       (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.  is returned
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Elliptic Integral](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_rf.cpp}
//================================================================================================
  inline constexpr auto ellint_rf = eve::functor<ellint_rf_t>;
//================================================================================================
//! @}
//================================================================================================
}
namespace kyosu::_
{
  template<typename T, eve::callable_options O >
  constexpr auto ellint_rf_(KYOSU_DELAY(), O const& o, T x, T y, T z) noexcept
  {
    using r_t = eve::underlying_type_t<T>;
    auto tol = [&](){
      if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(x);
      else return eve::eps(eve::as(real(x)));
    }();
    T    xn   = x;
    T    yn   = y;
    T    zn   = z;
    T    an   = kyosu::average(x, y, z);
    T    a0   = an;
    r_t epsi = eve::pow_abs(3 *tol, -eve::rec(r_t(6)));
    r_t q  = epsi * kyosu::maxabs(an - xn, an - yn, an - zn);
    r_t fn = eve::one(eve::as<r_t>());

    // duplication
    unsigned k  = 1;
    r_t hf = half(as(real(x)));
    for( ; k < 30; ++k )
    {
      T root_x = kyosu::sqrt(xn);
      T root_y = kyosu::sqrt(yn);
      T root_z = kyosu::sqrt(zn);
      root_x = if_else(real(root_x) < 0, -root_x, root_x);
      root_y = if_else(real(root_y) < 0, -root_y, root_y);
      root_z = if_else(real(root_z) < 0, -root_z, root_z);
      auto lambda = root_x * root_y + root_x * root_z + root_y * root_z;
      an       =  kyosu::average(an, lambda) * hf;
      xn       =  kyosu::average(xn, lambda) * hf;
      yn       =  kyosu::average(yn, lambda) * hf;
      zn       =  kyosu::average(zn, lambda) * hf;
      q *= r_t(0.25);
      fn *= r_t(4);
      if( eve::all(q < kyosu::abs(an)) ) break;
    }
    T denom = kyosu::rec(an * fn);
    T xx    = (a0 - x) * denom;
    T yy    = (a0 - y) * denom;
    T zz    = -xx - yy;

    // Taylor series expansion to the 7th order
    T p  = xx * yy;
    T e2 = kyosu::fnma(zz, zz, p);
    T e3 = p * zz;
    constexpr r_t c0 = r_t(1/14.0);
    constexpr r_t c1 = r_t(3/104.0);
    constexpr r_t c2 = r_t(-1/10.0);
    constexpr r_t c4 = r_t(1/24.0);
    constexpr r_t c5 = r_t(-3/44.0);
    constexpr r_t c6 = r_t(-5/208.0);
    constexpr r_t c7 = r_t(-1/16.0);
    return (kyosu::fma(e3,
                       kyosu::fma(e3, c1, c0),
                       kyosu::fma(e2, (c2 + e3 * c5 + e2 * (c4 + e2 * c6 + e3 * c7)), kyosu::one(as(x)))))
      / kyosu::sqrt(an);
  }
}
