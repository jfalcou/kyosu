//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/hypergeometric.hpp>
#include <kyosu/functions/acos.hpp>
#include <kyosu/functions/cos.hpp>

namespace kyosu
{
  template<typename Options>
  struct legendre_t : eve::strict_elementwise_callable<legendre_t, Options
                                                       , eve::successor_option, kyosu::type_1_option, kyosu::type_2_option, kyosu::type_3_option
                                                       , eve::p_kind_option, eve::q_kind_option
                                                  , eve::condon_shortley_option, eve::associated_option, eve::spherical_option>
  {
    template<concepts::real N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N nn, Z zz) const noexcept -> decltype(nn+zz)
    {
      using r_t = decltype(nn+zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto n = r_t(nn);
      auto z = r_t(zz);
//       if constexpr(Options::contains(eve::q_kind))
//       {
//         auto np3o2 = n+u_t(1.5);
//         auto np1 = kyosu::inc(n);
//         auto hf = eve::half(eve::as<u_t>());
//         auto gam1_5 =  u_t(2.658680776358274);
//         auto r = hypergeometric(rec(sqr(z)), kumi::tuple{inc(n*hf), np1*hf}, kumi::tuple{np3o2});
//         r = gam1_5*kyosu::tgamma(np1)*r*kyosu::tgamma_inv(np3o2)*kyosu::pow(2*z, -kyosu::inc(n));
//         return r; //if_else(is_real(z), complex(real(r)), r);
//       }
//       else
//       {
       auto r = kyosu::hypergeometric(oneminus(z)*eve::half(eve::as<u_t>()), kumi::tuple{-n, n+1}, kumi::tuple{u_t(1.0)});
       return if_else(is_real(z), complex(real(r)), r);
//      }
    }

    template<concepts::real N, concepts::real Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, Z z) const noexcept -> decltype(n+complex(z))
    { return (*this)(n, complex(z)); }

    template<concepts::real N, concepts::real M, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N nn, M mm, Z zz) const noexcept -> decltype(nn+mm+zz)
    {
      using r_t = decltype(nn+mm+zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto n = r_t(nn);
      auto m = r_t(mm);
      auto z = r_t(zz);
 //      if constexpr(Options::contains(eve::q_kind))
//       {
//         auto np3o2 = n+u_t(1.5);
//         auto np1 = kyosu::inc(n);
//         auto hf = eve::half(eve::as<u_t>());
//         auto gam1_5 =  u_t(2.658680776358274);
//         auto r = hypergeometric(rec(sqr(z)), kumi::tuple{inc(n*hf), np1*hf}, kumi::tuple{np3o2});
//         r = gam1_5*kyosu::tgamma(np1)*r*kyosu::tgamma_inv(np3o2)*kyosu::pow(2*z, -kyosu::inc(n));
//         return r; //if_else(is_real(z), complex(real(r)), r);
//       }
//       else
      r_t factor = one(eve::as<r_t>());
      if constexpr(Options::contains(kyosu::type_2))
      {
        factor = kyosu::pow(inc(z), m/2)/kyosu::pow(kyosu::oneminus(z), m/2);
      }
      else if constexpr(Options::contains(kyosu::type_3))
      {
        factor = kyosu::pow(inc(z), m/2)/kyosu::pow(dec(z), m/2);
      }
      auto r = kyosu::hypergeometric(kyosu::oneminus(z)*eve::half(eve::as<u_t>()), kumi::tuple{-n, n+1}, kumi::tuple{kyosu::oneminus(m)})*kyosu::tgamma_inv(kyosu::oneminus(m))*factor;
      return r;
    }

    template<concepts::real N, concepts::real M, concepts::real Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, M m, Z z) const noexcept -> decltype(n+m+complex(z))
    { return (*this)(n, m, complex(z)); }

//     // Recurrence relation for Legendre polynomials:
//    template<concepts::cayley_dickson Z,  concepts::cayley_dickson T>
//     KYOSU_FORCEINLINE constexpr auto  operator()( Z z, T tn, T tnm1) const noexcept -> decltype(z+tn)
//     {
//       return complex(2*z*tn-tnm1);
//     }

//       template<concepts::real Z, concepts::real T>
//     KYOSU_FORCEINLINE constexpr auto operator()(Z z, T tn,  T tnm1) const noexcept -> decltype(complex(z+tn))
//         requires(Options::contains(eve::successor))
//     {
//       return (*this)[eve::successor](complex(z), tn, tnm1);
//     }


    KYOSU_CALLABLE_OBJECT(legendre_t, legendre_);
  };


//================================================================================================
//! @addtogroup functions
//! @{
//!   @var legendre
//!   @brief Computes the value of the Legendre and associated
//!   Legendre functions of order `n` ( and 'm`) at `x`:
//!
//!   For positive integer `n` and 'm` the standard legendre functions are polynomials:
//!    * The Legendre polynomial of order n is given by \f$\displaystyle \mbox{L}_{n}(x)
//!      = \frac{e^x}{n!}\frac{d^n}{dx^n}(x^ne^{-x})\f$.
//!    *  The associated legendre polynomial is given by  \f$\displaystyle \mbox{L}_{n}^{m} =
//!      (-1)^m\frac{d^m}{dx^m}\mbox{L}_{n+m}(x)\f$.
//!
//!    However the function legendre must and can be called with real or complex parameters.
//!
//!  The legendre functions have 2 flavours `p_kind` and 'q_kind` and the legendre associated 2 flavours and 3 types
//!    * the flavours are controlled by the p_kind and q_kind  options
//!    * the types by `type_1`, `type_2` and `type_3` options:
//!        - `type_1` is defined only for within the unit circle in the complex plane. `type_2` represents an analytic continuation of `type_1` outside the unit circle.
//!        - `type_2` functions have branch cuts from \f$-\infty\f$ to -1 and from 1 to \f$infty\f$ in the complex plane.
//!        - `type_3` functions have a single branch cut from \f$-\infty\f$ to +1.
//!
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      auto constexpr legendre(kyosu::concepts::real auto n, kyosu::concepts::cayley_dickson auto z) noexcept; // 1
//!      auto constexpr legendre(kyosu::concepts::real auto n, kyosu::concepts::real auto z)           noexcept; // 1
//!      auto constexpr legendre(kyosu::concepts::real auto n, kyosu::concepts::real auto , kyosu::concepts::cayley_dickson auto z) noexcept; // 1
//!      auto constexpr legendre(kyosu::concepts::real auto n, kyosu::concepts::real auto m, kyosu::concepts::real auto z)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto legendre[conditional_expr auto c](/* any previous overload */)                 noexcept; // 2
//!      constexpr auto legendre[logical_value auto m](/* any previous overload */)                    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto legendre[p_kind](/* any previous overload */)                                  noexcept; // 1
//!      constexpr auto legendre[q_kind](i/* any previous overload */)                                 noexcept; // 3
//!      constexpr auto legendre[successor](integral_value auto l,integral_value auto m,
//!                                         kyosu::concepts::cayley_dickson auto x,
//!                                         kyosu::concepts::cayley_dickson auto ln,
//!                                         kyosu::concepts::cayley_dickson auto lnm1)   noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`, `m`, `l` : [integral positive arguments](@ref eve::integral_value).
//!     * `x` : [floating argument](@ref eve::floating_value).
//!     * `ln`, `lnm1` : [integral positive arguments](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      1. The value of the Legendre polynomial  of order `n` at `x` is returned.
//!      2. The value of the Legendre polynomial  of order `n` at `x` of the  second kind is returned.
//!      3. The value of the associated legendre polynomial of orders `n`, `m` at `x` is returned.
//!      4. multiplies the associated legendre polynomial value by the Condon-Shortley phase \f$(-1)^m\f$
//!        to match the definition given by Abramowitz and Stegun (8.6.6). This is currently
//!        the version implemented in boost::math.
//!      5. returns the spherical associated Legendre function of degree l, order m, and polar angle theta in radian
//!         (that is the classical spherical harmonic with \f$\phi = 0\f$),
//!         i.e. \f$\displaystyle (-1)^m\frac{(2l+1)(l-m)!}{4\pi(l+m)!}\mbox{P}^m_{l}(\cos\theta)\f$
//!      6. The `successor` option implements the three term recurrence relation for the
//!         (associated) Legendre functions, \f$\displaystyle \mbox{P}^m_{l+1} =
//!         \left((2l+1)\mbox{P}^m_{l}(x)-l\mbox{P}^m_{l-1}(x)\right)/(l+m+1)\f$
//!         (\f$m = 0\f$ and no \f$m\f$ in call are equivalent here).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Classical Orthogonal Polynomials](https://dlmf.nist.gov/18.3)
//!   *  [C++ standard reference: legendre](https://en.cppreference.com/w/cpp/numeric/special_functions/legendre)
//!   *  [Wolfram MathWorld: Legendre Polynomial](https://mathworld.wolfram.com/LegendrePolynomial.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/legendre.cpp}
//================================================================================================
  inline constexpr auto legendre = eve::functor<legendre_t>;
//================================================================================================
//! @}
//================================================================================================
}
