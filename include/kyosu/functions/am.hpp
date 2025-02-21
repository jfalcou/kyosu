//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/jacobi_elliptic.hpp>
#include <eve/module/elliptic/ellint_1.hpp>
#include <eve/module/elliptic/am.hpp>
#include <kyosu/functions/sqr.hpp>

namespace kyosu
{

  template<typename Options>
  struct am_t : eve::strict_elementwise_callable<am_t, Options, eve::modular_option,
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
//!       constexpr Z       am( real<Z>   z, real<U> m)               noexcept; //1
//!       constexpr auto    am(complex<Z> z, real<U> m)               noexcept; //1
//!
//!      //Semantic modifiers
//!      constexpr Z    am[modular]( real<Z>      z, real<U> alpha)   noexcept; //1
//!      constexpr auto am[modular](complex<Z>    z, real<U> alpha)   noexcept; //1
//!      constexpr Z    am[eccentric]( real<Z>    z, real<U> m)       noexcept; //1
//!      constexpr auto am[eccentric](complex<Z>  z, real<U> m)       noexcept; //1
//!      constexpr auto am[threshold = tol]( real<Z>   z, real<U> k)  noexcept; //1
//!      constexpr auto am[threshold = tol](complex<Z> z, real<U> k)  noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `u`: argument.
//!     * `m`: amplitude parameter (\f$0\le m\le 1\f$).
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
//!   Thus, they can be used interchangeably up to roundings errors by giving the right option.
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
  template<typename Z, typename M, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto am_(KYOSU_DELAY(), O const& o, Z u, M m) noexcept
  {
    auto tol = [&](){
      if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(m);
      else return eve::epsilon(eve::maximum(eve::abs(m)));
    }();
    m =  eve::abs(m);
    if (O::contains(eve::modular)) m = eve::sin(m);
    else if (O::contains(eve::eccentric)) m = eve::sqrt(m);
    if (eve::all(is_real(u))) return kyosu::complex(eve::am(kyosu::real(u), m));

    auto [phi, psi] = u;
    auto [s,c,d] = eve::jacobi_elliptic[eve::threshold = tol](phi, m);
    auto mc = eve::sqrt(eve::oneminus(eve::sqr(m)));
    auto [s1,c1,d1] = eve::jacobi_elliptic[eve::threshold = tol](psi,mc);
    auto x0 = s*d1;
    auto x1 = c*c1;
    auto y  = s1*d;
    auto km = eve::ellint_1(m);
    auto nx = eve::floor ((phi+2*km )/(4*km));
    return kyosu::complex(eve::atan2[eve::pedantic](x0,x1), eve::atanh(y)) + eve::two_pi(as(phi))*nx;
  }
}
