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
#include <kyosu/functions/cos.hpp>

namespace kyosu
{
  template<typename Options>
  struct tchebytchev_t : eve::strict_elementwise_callable<tchebytchev_t, Options
                                                          , eve::successor_option, eve::kind_1_option, eve::kind_2_option>
  {
    template<concepts::real N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N nn, Z zz) const noexcept -> decltype(nn+zz)
    {
      using r_t = decltype(nn+zz);
      using u_t = eve::underlying_type_t<r_t>;
      auto n = r_t(nn);
      auto z = r_t(zz);
      if constexpr(!Options::contains(kind_2))
      {
        auto r = kyosu::hypergeometric(oneminus(z)*eve::half(eve::as<u_t>()), kumi::tuple{-n, n}, kumi::tuple{u_t(0.5)});
        return if_else(is_real(z), complex(real(r)), r);
      }
      else
      {
        auto r = kyosu::inc(n)*hypergeometric(oneminus(z)*eve::half(eve::as<u_t>()), kumi::tuple{-n, n+2}, kumi::tuple{u_t(1.5)});
        return if_else(is_real(z), complex(real(r)), r);
      }
    }

    template<concepts::real N, concepts::real Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, Z z) const noexcept -> decltype(n+complex(z))
    { return (*this)(n, complex(z)); }


    // Recurrence relation for Tchebytchev polynomials:
   template<concepts::cayley_dickson Z,  concepts::cayley_dickson T>
    KYOSU_FORCEINLINE constexpr auto  operator()( Z z, T tn, T tnm1) const noexcept -> decltype(z+tn)
    {
      return complex(2*z*tn-tnm1);
    }

      template<concepts::real Z, concepts::real T>
    KYOSU_FORCEINLINE constexpr auto operator()(Z z, T tn,  T tnm1) const noexcept -> decltype(complex(z+tn))
        requires(Options::contains(eve::successor))
    {
      return (*this)[eve::successor](complex(z), tn, tnm1);
    }


    KYOSU_CALLABLE_OBJECT(tchebytchev_t, tchebytchev_);
  };


//================================================================================================
//! @addtogroup functions
//! @{
//!   @var tchebytchev
//!   @brief Computes the value of the Tchebytchev polynomial of order `n` at `z`:
//!
//!    * The Tchebytchev polynomial of order n is given by \f$ \displaystyle \mbox{T}_{n}(x)
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
//!      auto constexpr tchebytchev(kyosu::concepts::real auto n, kyosu::concepts::cayley_dickson auto z) noexcept; // 1
//!      auto constexpr tchebytchev(kyosu::concepts::real auto n, kyosu::concepts::real auto z)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto tchebytchev[conditional_expr auto c](/* any previous overload */)                 noexcept; // 2
//!      constexpr auto tchebytchev[logical_value auto m](/* any previous overload */)                    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto tchebytchev[kind_1](/* any previous overload */)                                  noexcept; // 1
//!      constexpr auto tchebytchev[kind_2](i/* any previous overload */)                                 noexcept; // 3
//!      constexpr auto tchebytchev[successor]( kyosu::concepts::cayley_dickson auto z,
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
//!      3. evaluates the nth polynomial of tchebytchev of second kind
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
//!   @godbolt{doc/polynomial/regular/tchebytchev.cpp}
//================================================================================================
  inline constexpr auto tchebytchev = eve::functor<tchebytchev_t>;
//================================================================================================
//! @}
//================================================================================================
}
