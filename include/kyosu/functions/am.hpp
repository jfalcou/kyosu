//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{

  template<typename Options>
  struct am_t : eve::elementwise_callable<am_t, Options>
  {
    template<eve::floating_value T0, eve::floating_value T1>
    requires(concepts::real<T0> && concepts::real<T1>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return eve::am(a, b); }

    template<eve::floating_value T0, eve::floating_value T1>
    requires(concepts::real<T1> && concepts::complex<T0>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }


    KYOSU_CALLABLE_OBJECT(am_t, am_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  am
//!   @brief Computes Jacobi's Amplitude function.
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
//!      // Regular overload
//!      template<eve;scalar_value U, kyosu::concepts::real Z>    constexpr Z    am(real<U> m, real<Z> z)                 noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto am(real<U> m, complex<Z> z)              noexcept; //1
//!
//!      //Semantic modifiers
//!      template<eve;scalar_value U, kyosu::concepts::real Z>    constexpr Z    am[modular](real<U> alpha, real<Z> z)        noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto am[modular](real<U> alpha, complex<Z> z)     noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::real Z>    constexpr Z    am[eccentric](real<U> k, real<Z> z)          noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto am[eccentric](real<U> k, complex<Z> z)       noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto am[threshold = tol](real<U> t, real<Z> z)    noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto am[threshold = tol](real<U> t, complex<Z> z) noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `u`: argument.
//!     * `m`: amplitude parameter (\f$0\le m\le 1).
//!     * `alpha `: modular angle in radian.
//!     * `k`: elliptic modulus (eccentricity) .
//!     * `tol': accuracy tolerance (by defaut [epsilon](@ref eve::epsilon).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `l`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!
//!   **Return value**
//!
//!      1. return the jacobian amplitude function. Take care that the meaning of the second parameters
//!         depends on the option used (see note below).
//!
//! @note
//!   * \f$\alpha\f$ is named the modular angle given in radian (modular option).
//!   * \f$ k = \sin\alpha \f$ is named the elliptic modulus or eccentricity (eccentric option).
//!   * \f$ m = k^2 = \sin^2\alpha\f$ is named the parameter (no option).
//!   Each of the above three quantities is completely determined by any of the others (given that they are non-negative).
//!   Thus, they can be used interchangeably up to roundings erreors by giving the right option.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: am](https://en.cppreference.com/w/cpp/numeric/special_functions/am)
//!   *  [DLMF: Jacobi Amplitude](https://dlmf.nist.gov/22.16)
//!   *  [Wolfram MathWorld: Jacobi Amplitude](https://mathworld.wolfram.com/JacobiAmplitude.html)
//!   *  [Wikipedia: Jacobi elliptic functions](https://en.wikipedia.org/wiki/Jacobi_elliptic_functions)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/am.cpp}
//======================================================================================================================
  inline constexpr auto am = eve::functor<am_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename M, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto am_(KYOSU_DELAY(), O const&, Z u, M x) noexcept
  T am_(EVE_REQUIRES(cpu_), O const& o, T u, M x) noexcept
  {
    auto tol = [&](){
      if constexpr (O::contains(threshold)) return o[threshold].value(x);
      else  return eve::epsilon(x);
    }();
    x =  abs(x);
    if (O::contains(modular)) x = sin(x);
    else if (O::contains(eccentric)) x = sqrt(x);

    auto [phi, psi] = u;
    auto [s,c,d] = eve::am[threshold = tol](phi, x);
    if (all(is_real(phi)) return zip{s, c, d};

    auto [s1,c1,d1] = eve::am[threshold = tol](psi,oneminus(m));

    idelta = rec(sqr(c1) + m*sqr(s)*sqr(s1));
    auto sn = complex(s*d1, c*d*s1*c1)*idelta;
    auto cn = complex(c*c1, -s*d*s1*d1)*idelta;
    auto dn = complex(d*c1*d1, -m*s*c*s1)*idelta;
    return zip{sn, cn, dn};
  }
}
