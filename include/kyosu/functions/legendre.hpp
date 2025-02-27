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
                                                       , eve::successor_option, eve::p_kind_option, eve::q_kind_option
                                                  , eve::condon_shortley_option, eve::associated_option, eve::spherical_option>
  {
    template<concepts::real N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N nn, Z zz) const noexcept -> decltype(nn+zz)
    {
      using r_t = decltype(nn+zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto n = r_t(nn);
      auto z = r_t(zz);
      if constexpr(Options::contains(eve::q_kind))
      {
        auto np3o2 = n+u_t(1.5);
        auto np1 = kyosu::inc(n);
        auto hf = eve::half(eve::as<u_t>());
        auto gam1_5 =  u_t(2.658680776358274);
        auto r = hypergeometric(rec(sqr(z)), kumi::tuple{inc(n*hf), np1*hf}, kumi::tuple{np3o2});
        r = gam1_5*kyosu::tgamma(np1)*r*kyosu::tgamma_inv(np3o2)*kyosu::pow(2*z, -kyosu::inc(n));
        return r; //if_else(is_real(z), complex(real(r)), r);
      }
      else
      {
       auto r = kyosu::hypergeometric(oneminus(z)*eve::half(eve::as<u_t>()), kumi::tuple{-n, n+1}, kumi::tuple{u_t(1.0)});
       return if_else(is_real(z), complex(real(r)), r);
      }
    }

    template<concepts::real N, concepts::real Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, Z z) const noexcept -> decltype(n+complex(z))
    { return (*this)(n, complex(z)); }


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
//!   @brief Computes the value of the Legendre polynomial of order `n` at `z`:
//!
//!    * The Legendre polynomial of order n is given by \f$ \displaystyle \mbox{T}_{n}(x)
//!      = \cos(n\arccos(x))\f$
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
//!
//!      // Lanes masking
//!      constexpr auto legendre[conditional_expr auto c](/* any previous overload */)                 noexcept; // 2
//!      constexpr auto legendre[logical_value auto m](/* any previous overload */)                    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto legendre[p_kind](/* any previous overload */)                                  noexcept; // 1
//!      constexpr auto legendre[q_kind](i/* any previous overload */)                                 noexcept; // 3
//!      constexpr auto legendre[successor]( kyosu::concepts::cayley_dickson auto z,
//!                                                           kyosu::cayley_dickson auto tn,
//!                                                           kyosu::cayley_dickson auto tnm1)            noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral positive arguments](@ref eve::integral_value).
//!              (note that negative values return a NaN)
//!     * `x` :  [real floating argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!      1.The value of the polynomial at `z` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. evaluates the nth polynomial of legendre of second kind
//!         \f$ \displaystyle U_n(z) =  \frac{\sin(n\arccos z)}{\sin(\arccos z)}\f$.
//!      4. computes the value of \f$T_{n+1}(z)\f$ knowing the values tn = \f$T_n(z)\f$ and
//!         tnm1 = \f$T_{n-1}(z)\f$,
//!         This call can be used to create a sequence of values evaluated at the same `z`
//!         and for rising `n`.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Chebyshev_polynomials]( https://en.wikipedia.org/wiki/Chebyshev_polynomials)
//!   *  [Wolfram MathWorld: first kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheFirstKind.html)
//!   *  [Wolfram MathWorld: second kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheSecondKind.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/legendre.cpp}
//================================================================================================
  inline constexpr auto legendre = eve::functor<legendre_t>;
//================================================================================================
//! @}
//================================================================================================
}
