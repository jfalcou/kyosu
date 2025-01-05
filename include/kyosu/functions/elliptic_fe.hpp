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
    template<concepts::real T0, concepts::real T1>
    constexpr KYOSU_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept
    { return (*this)(kyosu::complex(a), b); }

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
    std::cout << "m  "<< m << std::endl;

// % to avoid singularity of COT(phi) at zero add EPS
// I = find (abs(phi) < eps);
// phi(I) = eps;
// I = [];
    auto thresh = eve::sqr(eve::eps(as(phi)));
    phi =  if_else(eve::abs(phi) < thresh, thresh, phi);

// % finding the roots of the equation
// % X^2 - (cot(phi)^2+m*sinh(psi)^2*csc(phi)^2-1+m)X - (1-m)*cot(phi)^2 = 0
// b = -(cot(phi).^2 + m.*sinh(psi).^2.*csc(phi).^2-1+m);
// c = -(1-m).*cot(phi).^2;
    auto b = -(eve::sqr(eve::cot(phi)) + m2*eve::sqr(eve::sinh(psi)*eve::csc(phi))-1+m2); //*eve::half(eve::as(phi));
    auto c = -(1-m2)*eve::sqr(eve::cot(phi));
    std::cout << "b     " << b << std::endl;
    std::cout << "c     " << c << std::endl;
// X1 = -b/2 + sqrt(b.^2/4-c);
// I = find(X1>=0);
    auto X1 = -b/2+eve::sqrt(eve::sqr(b)/4-c);
    std::cout << "X1 "<< X1 << std::endl;
// if length(I) ~= length(u)
//     X2 = -b/2 - sqrt(b.^2/4-c);
//     J = find(X2>=0);
// end

// if( ~isempty(I) )
//     lambda(I) = acot( sqrt(X1(I)) );
//     mu(I)     = atan( sqrt(1./m(I).*(tan(phi(I)).^2.*cot(lambda(I)).^2 - 1)) );
// end
    auto lambda = eve::acot(eve::sqrt(X1));
    auto mu     = eve::atan( rec(m)*eve::sqrt(eve::dec(eve::sqr(tan(phi)*eve::cot(lambda)))));
//     std::cout << "lambda " << lambda << std::endl;
//     std::cout << "mu     " << mu     << std::endl;
// if( ~isempty(J) )
//     lambda(J) = acot( sqrt(X2(J)) );
//     mu(J)     = atan( sqrt(1./m(J).*(tan(phi(J)).^2.*cot(lambda(J)).^2 - 1)) );
// end

// % change of variables taking into account periodicity ceil to the right
// lambda = (-1).^floor(phi/pi*2).*lambda + pi*ceil(phi/pi-0.5+eps);
// mu     = sign(psi).*real(mu);
    lambda = eve::sign_alternate(eve::floor(2*phi*eve::inv_pi(eve::as(phi))))*lambda+eve::pi(eve::as(phi))*eve::ceil(phi/eve::pi(eve::as(phi))-eve::half(eve::as(phi))+eve::eps(eve::as(phi)));
    mu     = eve::sign(psi)*mu;
//     std::cout << "--lambda " << lambda << std::endl;
//     std::cout << "--mu     " << mu     << std::endl;
    // [F1(:),E1(:)] = elliptic12(lambda, m, tol);
// [F2(:),E2(:)] = elliptic12(mu, 1-m, tol);
    auto mc = eve::sqrt(eve::oneminus(m2));
    lambda =  if_else(is_real(u), phi, lambda);
    auto f1 = eve::ellint_1/*[eve::threshold = tol]*/(lambda, m);
    auto e1 = eve::ellint_2/*[eve::threshold = tol]*/(lambda, m);
    auto f2 = eve::ellint_1/*[eve::threshold = tol]*/(mu, mc);
    auto e2 = eve::ellint_2/*[eve::threshold = tol]*/(mu, mc);
    f1 = if_else(is_imag(u), zero, f1);
    e2 = if_else(is_eqz(mu), zero, e2);
    std::cout << "f1     " << f1     << std::endl;
    std::cout << "e1     " << e1     << std::endl;
    std::cout << "f2     " << f2     << std::endl;
    std::cout << "mu     " << mu     << std::endl;
    std::cout << "mc     " << mc     << std::endl;
    std::cout << "e2     " << e2     << std::endl;

// % complex values of elliptic integral of the first kind
// Fi = F1 + sqrt(-1)*F2;
    auto f = kyosu::complex(f1, f2);
// % some calucation optimiziation
// sin_lam = sin(lambda); cos_lam = cos(lambda);
// sin_mu = sin(mu); cos_mu = cos(mu);
    auto [sin_lam, cos_lam] = eve::sincos(lambda);
    auto [sin_mu , cos_mu ] = eve::sincos(mu);
// b1 = m.*sin_lam.*cos_lam.*sin_mu.^2.*sqrt(1-m.*sin_lam.^2);
// b2 = sin_mu.*cos_mu.*(1-m.*sin_lam.^2).*sqrt(1-(1-m).*sin_mu.^2);
// b3 = cos_mu.^2 + m.*sin_lam.^2.*sin_mu.^2;
    auto sin_mu2 = eve::sqr(sin_mu);
    auto sin_lam2 = eve::sqr(sin_lam);
    auto b1 = m2*sin_lam*cos_lam*sin_mu2*eve::sqrt(eve::oneminus(m2*sin_lam2));
    auto b2 = sin_mu*cos_mu*(1-m2*sin_lam2)*eve::sqrt(1-oneminus(m2)*sin_mu2);
    auto b3 = eve::sqr(cos_mu) + m*sin_lam2*sin_mu2;
    std::cout << "b1     " << b1     << std::endl;
    std::cout << "b2     " << b2     << std::endl;
    std::cout << "b3     " << b3     << std::endl;

// % complex values of elliptic integral of the second kind
// Ei(:) = (b1 + sqrt(-1)*b2)./b3;
// Ei(:) = Ei(:) + E1(:) + sqrt(-1)*(-E2(:) + F2(:));
    auto e =  kyosu::complex(b1, b2)/b3;
    std::cout << "e " << e << std::endl;
    e = e + kyosu::complex(e1, if_else(is_real(u), zero, f2-e2));
    kyosu::real(e) =  if_else(is_imag(u), zero, real(e));
    std::cout << "-- e " << e << std::endl;
// [K,Ee] = ellipke(m);
// % complex values of zeta function
// Zi(:) = Ei(:) - Ee(:)./K(:).*Fi(:);
    return eve::zip(f, e);
  }
}
