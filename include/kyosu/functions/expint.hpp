//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/tricomi.hpp>

namespace kyosu
{
  template<typename Options>
  struct expint_t : eve::elementwise_callable<expint_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto operator()(Z const& z) const noexcept
    { return exp(-z)*kyosu::tricomi(z, Z(1.0), Z(1.0)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::exp_int(v); }

    template<concepts::cayley_dickson Z, typename T>
    KYOSU_FORCEINLINE constexpr auto operator()(T n, Z z) const noexcept
    {
      using r_t = decltype(z+n);
      return kyosu::pow(z, kyosu::dec(r_t(n)))*kyosu::exp(-z)*kyosu::tricomi(r_t(z), r_t(n), r_t(n));
    }

    template<concepts::real V, concepts::real T >
    KYOSU_FORCEINLINE constexpr V operator()(V v, T x ) const noexcept
    {
      return eve::exp_int(kyosu::complex(v), x);
    }

    KYOSU_CALLABLE_OBJECT(expint_t, expint_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expint
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
//!      constexpr auto expint(concepts::cayley_dickson auto x)                                   noexcept; // 1
//!      constexpr auto expint(concepts::cayley_dickson auto n, floating_value auto x)            noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: order. If not present taken to be 1.
//!     * `x`: cayley_dickson or real argument.
//!
//!   **Return value**
//!
//!     1. The value of the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$, is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld:Exponential Integral ](https://mathworld.wolfram.com/ExponentialIntegral.html)
//!   *  [DLMF: Generalized Exponential Integral](https://dlmf.nist.gov/8.19#i)
//!   *  [Wikipedia: Exponential integral](https://en.wikipedia.org/wiki/Exponential_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/expint.cpp}
//======================================================================================================================
  inline constexpr auto expint = eve::functor<expint_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
