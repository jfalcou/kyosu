//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <eve/module/elliptic/jacobi_elliptic.hpp>
#include <kyosu/functions/sqr.hpp>

namespace kyosu
{

  template<typename Options>
  struct jacobi_elliptic_t : eve::strict_elementwise_callable<jacobi_elliptic_t, Options, eve::modular_option,
                                                 eve::eccentric_option, eve::threshold_option>
  {
    template<concepts::real T0, concepts::real T1>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept
    { return (*this)(kyosu::complex(a), b); }

    template<concepts::complex T0, concepts::real T1>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept
    { return KYOSU_CALL(a, b); }


    KYOSU_CALLABLE_OBJECT(jacobi_elliptic_t, jacobi_elliptic_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  jacobi_elliptic
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
//!      template<eve;scalar_value U, kyosu::concepts::real Z>    constexpr Z    jacobi_elliptic(real<U> m, real<Z> z)                 noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto jacobi_elliptic(real<U> m, complex<Z> z)              noexcept; //1
//!
//!      //Semantic modifiers
//!      template<eve;scalar_value U, kyosu::concepts::real Z>    constexpr Z    jacobi_elliptic[modular](real<U> alpha, real<Z> z)        noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto jacobi_elliptic[modular](real<U> alpha, complex<Z> z)     noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::real Z>    constexpr Z    jacobi_elliptic[eccentric](real<U> k, real<Z> z)          noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto jacobi_elliptic[eccentric](real<U> k, complex<Z> z)       noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto jacobi_elliptic[threshold = tol](real<U> t, real<Z> z)    noexcept; //1
//!      template<eve;scalar_value U, kyosu::concepts::complex Z> constexpr auto jacobi_elliptic[threshold = tol](real<U> t, complex<Z> z) noexcept; //1
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
//!  @godbolt{doc/jacobi_elliptic.cpp}
//======================================================================================================================
  inline constexpr auto jacobi_elliptic = eve::functor<jacobi_elliptic_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, typename M, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto jacobi_elliptic_(KYOSU_DELAY(), O const& o, Z u, M m) noexcept
  {
    auto tol = [&](){
      if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(m);
      else return eve::epsilon(eve::maximum(eve::abs(m)));
    }();
    m =  eve::abs(m);
    if (O::contains(eve::modular)) m = eve::sin(m);
    else if (O::contains(eve::eccentric)) m = eve::sqrt(m);

    auto [phi, psi] = u;
    auto [s,c,d] = eve::jacobi_elliptic[eve::eccentric][eve::threshold = tol](phi, m);
    if (eve::all(is_real(u))) return eve::zip(kyosu::complex(s), kyosu::complex(c), kyosu::complex(d));

    auto mc = eve::oneminus(m);
    auto [s1,c1,d1] = eve::jacobi_elliptic[eve::eccentric][eve::threshold = tol](psi,mc);
    auto idelta = kyosu::rec(kyosu::sqr(c1) + m*kyosu::sqr(s)*kyosu::sqr(s1));
    auto sn = complex(s*d1, c*d*s1*c1)*idelta;
    auto cn = complex(c*c1, -s*d*s1*d1)*idelta;
    auto dn = if_else(u == one(as(u)), kyosu::one(as(u)), complex(d*c1*d1, -m*s*c*s1)*idelta);
    return eve::zip(sn, cn, dn);
  }
}
