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
#include <kyosu/functions/ellint_rf.hpp>
#include <kyosu/functions/ellint_rd.hpp>

namespace kyosu
{

  template<typename Options> struct ellint_rg_t : eve::elementwise_callable<ellint_rg_t, Options, eve::threshold_option>
  {
    template<eve::floating_value T0, eve::floating_value T1, eve::floating_value T2>
    constexpr KYOSU_FORCEINLINE as_cayley_dickson_like_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept
    {
      return eve::ellint_rg(a, b, c);
    }

    template<concepts::complex T0, concepts::complex T1, concepts::complex T2>
    constexpr KYOSU_FORCEINLINE as_cayley_dickson_like_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept
    requires(concepts::complex<T0> || concepts::complex<T1> || concepts::complex<T2>)
    {
      return KYOSU_CALL(a, b, c);
    }

    KYOSU_CALLABLE_OBJECT(ellint_rg_t, ellint_rg_);
  };

  //================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var ellint_rg
  //!   @brief Computes the Carlson's elliptic integral
  //!   \f$ \mathbf{R}_\mathbf{G}(x, y) = \frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi}
  //!   \scriptstyle\sqrt{x\sin^2\theta\cos^2\phi
  //!   +y\sin^2\theta\sin^2\phi
  //!   +z\cos^2\theta} \scriptstyle\;\mathrm{d}\theta\;\mathrm{d}\phi\f$
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <kyosu/kyosu.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto ellint_rg(auto x, auto y, auto z)                 noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto ellint_rg[conditional_expr auto c](/*all previous overloads*/)   noexcept; // 2
  //!      constexpr auto ellint_rg[logical_value auto m](/*all previous overloads*/)      noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z`:  complex or real arguments.
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. the value of the \f$\mathbf{R}_\mathbf{G}\f$ Carlson elliptic integral:
  //!       \f$\frac14 \int_{0}^{\infty}[(t+x)(t+y)(t+z)]^{-1/2}\left(\frac{x}{t+x}+\frac{y}{t+y}+\frac{z}{t+z}\right)t\;\mathrm{d}t\f$
  //!       is returned.
  //!       All of x, y, z may be 0 and those that are nonzero must lie in the complex plane cut
  //!       along the nonpositive real axis
  //!     2. [The operation is performed conditionnaly](@ref conditional)
  //!
  //!  @groupheader{External references}
  //!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
  //!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
  //!
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/ellint_rg.cpp}
  //================================================================================================
  inline constexpr auto ellint_rg = eve::functor<ellint_rg_t>;
  //================================================================================================
  //! @}
}
namespace kyosu::_
{
  template<typename T, eve::callable_options O>
  constexpr auto ellint_rg_(KYOSU_DELAY(), O const& o, T x, T y, T z) noexcept
  {
    auto ax = kyosu::abs(x);
    auto ay = kyosu::abs(y);
    auto az = kyosu::abs(z);
    using r_t = eve::underlying_type_t<T>;
    eve::swap_if(ax < ay, x, y);
    eve::swap_if(ax < az, x, z);
    eve::swap_if(ay > az, y, z);
    // now all(x >= z) and all(z >= y)
    auto root = kyosu::sqrt(x * y / z);
    root = if_else(eve::is_ltz(imag(root)), -root, root);
    return average(z * ellint_rf[o](x, y, z) - (x - z) * (y - z) * ellint_rd[o](x, y, z) * eve::third(as<r_t>()), root);
  }
}
