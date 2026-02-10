//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/elliptic/ellint_rc.hpp>
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/functions/sqrt.hpp>
#include <kyosu/functions/fma.hpp>
#include <kyosu/functions/fnma.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/functions/reverse_horner.hpp>

namespace kyosu
{

  template<typename Options> struct ellint_rc_t : eve::elementwise_callable<ellint_rc_t, Options, eve::threshold_option>
  {
    template<eve::floating_value T0, eve::floating_value T1>
    constexpr KYOSU_FORCEINLINE as_cayley_dickson_like_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    {
      return eve::ellint_rc(a, b);
    }

    template<typename T0, typename T1>
    constexpr KYOSU_FORCEINLINE as_cayley_dickson_like_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    requires(concepts::complex<T0> || concepts::complex<T1>)
    {
      return KYOSU_CALL(a, b);
    }

    KYOSU_CALLABLE_OBJECT(ellint_rc_t, ellint_rc_);
  };

  //================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var ellint_rc
  //!   @brief Computes the Carlson's elliptic integral
  //!   \f$  \mathbf{R}_\mathbf{C}(x, y) =
  //!   \frac12 \int_{0}^{\infty} \scriptstyle(t+x)^{-1/2}(t+y)]^{-1}\;\mathrm{d}t\f$.
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
  //!      constexpr auto ellint_rc(auto x, auto y)                           noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto ellint_rc[conditional_expr auto c](auto x, auto y)  noexcept; // 2
  //!      constexpr auto ellint_rc[logical_value auto m](auto x, auto y)     noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`: Can be a mix of complex and real floating values. `x`, `y` must be non zero
  //!       and have phase less in magnitude than \f$\pi\f$, with the exception that `x` may be 0.
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. the value of the Carlson degenerate elliptic integral:
  //!       \f$\mathbf{R}_\mathbf{C}(x, y) = \frac12 \int_{0}^{\infty}
  //!       \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$ is returned.
  //!     2. [The operation is performed conditionally](@ref conditional)
  //!
  //!  @groupheader{External references}
  //!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
  //!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/ellint_rc.cpp}
  //================================================================================================
  inline constexpr auto ellint_rc = eve::functor<ellint_rc_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
namespace kyosu::_
{
  template<typename T, eve::callable_options O>
  constexpr auto ellint_rc_(KYOSU_DELAY(), O const& o, T xx, T yy) noexcept
  {
    using r_t = eve::underlying_type_t<T>;
    auto tol = [&]() {
      if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(xx);
      else return eve::eps(eve::as<r_t>());
    }();
    auto internal_rc = [tol](auto x, auto y) {
      T xn = x;
      T yn = y;
      T an = kyosu::average(x, y, y);
      T a0 = an;
      r_t epsi = eve::pow_abs(3 * tol, -eve::rec(r_t(8)));
      auto q = epsi * kyosu::abs(an - xn);
      r_t fn = eve::one(eve::as<r_t>());

      // duplication
      auto hf = half(as(real(x)));
      for (unsigned k = 1; k < 30; ++k)
      {
        T root_xn = kyosu::sqrt(xn);
        T root_yn = kyosu::sqrt(yn);
        root_xn = if_else(real(root_xn) < 0, -root_xn, root_xn);
        root_yn = if_else(real(root_yn) < 0, -root_yn, root_yn);
        auto lambda = 2 * root_xn * root_yn + yn;
        an = kyosu::average(an, lambda) * hf;
        xn = kyosu::average(xn, lambda) * hf;
        yn = kyosu::average(yn, lambda) * hf;
        q *= r_t(0.25);
        fn *= r_t(4);
        if (eve::all(q < kyosu::abs(an))) break;
      }
      auto s = (y - a0) / (fn * an);
      // Taylor series expansion to the 7th order
      return kyosu::horner(s, r_t(9.0 / 8.0), r_t(159.0 / 208.0), r_t(9.0 / 22.0), r_t(3.0 / 8.0), r_t(1.0 / 7.0),
                           r_t(3.0 / 10.0), r_t(0.0), r_t(1.0)) /
             kyosu::sqrt(an);
    };
    auto test = eve::any(is_real(yy) && eve::is_ltz(kyosu::real(yy))); // compute Cauchy principal value on the cut
    if (eve::any(test))
    {
      auto fac = kyosu::sqrt(xx / (xx - yy));
      auto yr = if_else(test, yy, zero);
      auto xr = if_else(test, xx, zero);
      return kyosu::if_else(eve::is_lez(kyosu::real(yy)), internal_rc(xr - yr, -yr) * fac, internal_rc(xx, yy));
    }
    else return internal_rc(xx, yy);
  }
}
