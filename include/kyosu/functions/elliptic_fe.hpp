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
#include <eve/module/elliptic/ellint_2.hpp>

namespace kyosu
{

  template<typename Options>
  struct elliptic_fe_t : eve::strict_elementwise_callable<elliptic_fe_t, Options, eve::modular_option,
                                                 eve::eccentric_option, eve::threshold_option>
  {
    template<eve::floating_value T0, eve::floating_value T1>
    constexpr KYOSU_FORCEINLINE
    T0 operator()(T0 a, T1 b) const noexcept
    { return eve::zip(eve::ellint_1(a, b), eve::ellint_2(a, b)); }

    template<concepts::complex T0, concepts::real T1>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept -> decltype(eve::zip(T0(), T0()))
    { return KYOSU_CALL(a, b); }


    KYOSU_CALLABLE_OBJECT(elliptic_fe_t, elliptic_fe_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  elliptic_fe
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
//!       constexpr Z       elliptic_fe( real<Z>   z, real<U> m)               noexcept; //1
//!       constexpr auto    elliptic_fe(complex<Z> z, real<U> m)               noexcept; //1
//!
//!      //Semantic modifiers
//!      constexpr Z    elliptic_fe[modular]( real<Z>      z, real<U> alpha)   noexcept; //1
//!      constexpr auto elliptic_fe[modular](complex<Z>    z, real<U> alpha)   noexcept; //1
//!      constexpr Z    elliptic_fe[eccentric]( real<Z>    z, real<U> m)       noexcept; //1
//!      constexpr auto elliptic_fe[eccentric](complex<Z>  z, real<U> m)       noexcept; //1
//!      constexpr auto elliptic_fe[threshold = tol]( real<Z>   z, real<U> k)  noexcept; //1
//!      constexpr auto elliptic_fe[threshold = tol](complex<Z> z, real<U> k)  noexcept; //1
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
//!      1. return the elliptic incomplete functions or first and second kind. Tafe care that the meaning of the second parameters
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
//!   *  [DLMF: Legendre-F¢s Integrals](https://dlmf.nist.gov/19.2#ii)-A
//!   *  [Wolfram MathWorld: Jacobi Amplitude](https://functions.wolfram.com/EllipticIntegrals/EllipticF/)
//!   *  [Wolfram MathWorld: Jacobi Amplitude](https://functions.wolfram.com/EllipticIntegrals/EllipticE/)
//!   *  [Wikipedia: Elliptic integral](https://en.wikipedia.org/wiki/Elliptic_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic_fe.cpp}
//======================================================================================================================
  inline constexpr auto elliptic_fe = eve::functor<elliptic_fe_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, typename M, eve::callable_options O>
   constexpr auto elliptic_fe_(KYOSU_DELAY(), O const& o, Z u, M m)  noexcept -> decltype(eve::zip(Z(), Z()))
  {
    if constexpr(!std::same_as<eve::underlying_type_t<Z>, eve::underlying_type_t<M>>)
      return elliptic_fe[o](u, eve::convert(m, as<eve::underlying_type_t<Z>>()));
    else
    {
//     auto tol = [&](){
//       if constexpr (O::contains(eve::threshold)) return o[eve::threshold].value(m);
//       else return eve::epsilon(eve::maximum(eve::abs(m)));
//     }();
      m =  eve::abs(m);
      if (O::contains(eve::modular)) m = eve::sin(m);
      else if (O::contains(eve::eccentric)) m = eve::sqrt(m);
      auto [phi, psi] = u;

      if (eve::all(is_real(u))) return eve::zip(kyosu::complex(eve::ellint_1/*[eve::threshold = tol]*/(phi, m)),
                                                kyosu::complex(eve::ellint_2/*[eve::threshold = tol]*/(phi, m)));
      auto m2 = eve::sqr(m);
      auto thresh = eve::eps(eve::as(phi));
      phi =  if_else(eve::abs(phi) < thresh, thresh, phi); //avoiding singularity at 0

      auto b = -(eve::sqr(eve::cot(phi)) + m2*eve::sqr(eve::sinh(psi)*eve::csc(phi))-1+m2); //*eve::half(eve::as(phi));
      auto c = -(1-m2)*eve::sqr(eve::cot(phi));
      auto X1 = -b/2+eve::sqrt(eve::sqr(b)/4-c);
      auto lambda = eve::acot(eve::sqrt(X1));
      auto mu     = eve::atan( rec(m)*eve::sqrt(eve::dec(eve::sqr(tan(phi)*eve::cot(lambda)))));

      //  change of variables taking into account periodicity ceil to the right
      lambda = eve::sign_alternate(eve::floor(2*phi*eve::inv_pi(eve::as(phi))))*lambda+eve::pi(eve::as(phi))*eve::ceil(phi/eve::pi(eve::as(phi))-eve::half(eve::as(phi))+eve::eps(eve::as(phi)));
      mu     = eve::sign(psi)*mu;
      auto mc = eve::sqrt(eve::oneminus(m2));
      lambda =  if_else(is_real(u), phi, lambda);
      auto f1 = eve::ellint_1/*[eve::threshold = tol]*/(lambda, m);
      auto e1 = eve::ellint_2/*[eve::threshold = tol]*/(lambda, m);
      auto f2 = eve::ellint_1/*[eve::threshold = tol]*/(mu, mc);
      auto e2 = eve::ellint_2/*[eve::threshold = tol]*/(mu, mc);
      f1 = if_else(is_imag(u), zero, f1);
      e2 = if_else(is_eqz(mu), zero, e2);

      auto f = kyosu::complex(f1, f2);

      auto [sin_lam, cos_lam] = eve::sincos(lambda);
      auto [sin_mu , cos_mu ] = eve::sincos(mu);
      auto sin_mu2 = eve::sqr(sin_mu);
      auto sin_lam2 = eve::sqr(sin_lam);
      auto b1 = m2*sin_lam*cos_lam*sin_mu2*eve::sqrt(eve::oneminus(m2*sin_lam2));
      auto b2 = sin_mu*cos_mu*(1-m2*sin_lam2)*eve::sqrt(1-oneminus(m2)*sin_mu2);
      auto b3 = eve::sqr(cos_mu) + m2*sin_lam2*sin_mu2;
      auto e =  kyosu::complex(b1, b2)/b3;
      e += kyosu::complex(e1, if_else(is_real(u), zero, f2-e2));
      kyosu::real(e) =  if_else(is_imag(u), zero, real(e));

      auto test = eve::maxabs(phi, psi) < eve::eps(eve::as(kyosu::real(u)));
      if (eve::any(test))
      {
        f = if_else(test, u, f);
        e = if_else(test, u, e);
      }
      return eve::zip(f, e);
    }
  }
}
