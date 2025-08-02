//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/hyperg/hyp0_0.hpp>
#include <kyosu/details/hyperg/hyp0_1.hpp>
#include <kyosu/details/hyperg/hyp0_2.hpp>

#include <kyosu/details/hyperg/hyp1_0.hpp>
#include <kyosu/details/hyperg/hyp1_1.hpp>
#include <kyosu/details/hyperg/hyp1_2.hpp>

#include <kyosu/details/hyperg/hyp2_0.hpp>
#include <kyosu/details/hyperg/hyp2_1.hpp>
#include <kyosu/details/hyperg/hyp2_2.hpp>


namespace kyosu
{
  template<typename Options>
  struct hypergeometric_t : eve::strict_elementwise_callable<hypergeometric_t, Options, kyosu::regularized_option>
  {

    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};

    template<typename Z,  typename Tup1,  typename Tup2>       struct res
    {
      using cZ = complexify_t<Z>; 
      using Tup = kumi::result::cat_t<Tup1, Tup2, kumi::tuple<cZ>>;
      using type = kumi::apply_traits_t<result,Tup>;
    };

    template < typename T1,  typename T2,  typename T3>
    using res_t =  typename res<T1, T2, T3>::type;

    template<concepts::complex_like Z, kumi::product_type T1,  kumi::product_type T2>
    constexpr KYOSU_FORCEINLINE
    res_t<Z, T1, T2> operator()(Z z, T1 a, T2 b) const noexcept
    {
      if constexpr(!Options::contains(kyosu::regularized) || T2::empty())
      {
        if constexpr(concepts::real<Z>)
          return _::hyperg(kyosu::complex(z), a, b);
        else
          return _::hyperg(z, a, b);      }
      else
      {
        if constexpr(concepts::real<Z>)
          return _::hyperg(kyosu::complex(z), a, b, kyosu::regularized);
        else
          return _::hyperg(z, a, b, kyosu::regularized);
      }
    }
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var hypergeometric
//!   @brief Computes the hypergeometric function \f${}_pF_q(a_1, \dots, a_p; b_1,\dots, b_p; z)\f$ for \f$ 0 \le p,  q \le 2\f$.
//!
//!   **Defined in Header**
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
//!      //regular call
//!     constexpr auto hypergeometric(auto z, auto a, auto b)              noexcept; // 1;
//!
//!      // Semantic modifyiers
//!     constexpr auto hypergeometric[regularized](auto z, auto a, auto b) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`: homogeneous kumi tuple of size p
///!    * `b`: homogeneous kumi tuple of size q
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns the value at z of the hypergeometric function
//!       \f${}_pF_q(a_1, \dots, a_p; b_1,\dots, b_p; z) = \sum_{k = 0}^\infty \frac{(a_1)_k\dots (a_p]_k}{(b_1)_k\dots (b_q]_k}\frac{z^k}{k!}\f$.
//!       * if \f$p < q + 1\f$: the series converges absolutely for \f$z\in \mathbb{C}\f$, but can be very hard to compute accurately
//!       * if \f$p = q + 1\f$: the series converges absolutely for \f$|z| < 1\f$ and diverges for \f$|z| > 1\f$,
//!       * if \f$p > q + 1\f$: the series converges only for \f$z = 0\f$ unless the
//!          summation stops, an \f$a_i\f$ or \f$b_i\f$ being a non positive flint and the polynomial is so defined everywhere.
//!     2. With the regularized option the result is divided by the product of the \f$\Gamma(b_i)\f$ extended to the elements of the `b` tuple.
//!
//!     Up to now the only implemented functions are for size of `a` and `b` tuples running from 0 to 2. And some can have flaws.
//!
//!   @note hypergeometric functons are a kind of jungle. As **KYOSU** and **EVE** only use standard floating types as base of computations,
//!         overflows or lack of precision along large computation or huge values can degrade the accuracy.
//!         Moreover:
//!          - These fonctions always return complex outputs even if entries are all real ones.
//!          - The use of float-based inputs and computations are ok, but discouraged as overflows or lack of precision are much greater
//!            than double-based ones.
//!          - receiving a `fnan` ouput generally means than the computation did not end well.
//!          - receiving a `cinf` ouput generally means than the function is not defined here and that point is a singularity.
//!
//!  @groupheader{External references}
//!   *  [DLMF: Kummer Functions](https://dlmf.nist.gov/13.2)
//!   *  [Wolfram MathWorld:Confluent Hypergeometric Function of the Second Kind ](https://mathworld.wolfram.com/ConfluentHypergeometricFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Confluent hypergeometric function](https://en.wikipedia.org/wiki/Confluent_hypergeometric_function)
//!
//!  @groupheader{Implementation notes}
//!   * \f${}_0F_0(z, \{\}, \{\})\f$ is merely \f$e^z\f$.
//!   * \f${}_1F_0(z, \{a\}, \{\}\f$ is merely \f$ (1-z)^{-a}\f$
//!   * \f${}_0F_1(z, \{\}, \{b\})\f$, \f${}_0F_2(z, \{\}, \{b_0, b_1\})\f$,  \f${}_1F_1(z, \{a\}, \{b\})\f$, \f${}_1F_2(z, \{a\}, \{b_0, b_1\})\f$
//!      and \f${}_2F_2(z, \{a_0, a_1\}, \{b_0, b_1\})\f$ are always computed using the standard serie definition, it implies that their results are only correct
//!      for small values of `|z|`.
//!   * The serie defining \f${}_2F_0(z, \{a_0, a_1\}, \{\})\f$ is generally never convergent (but at zero) except when a component of `a` is a nonpositive integer.
//!   * Implementation of \f${}_2F_1(z, \{a_0, a_1\}, \{b\})\f$ which is the proper hypergeometric function is mainly inspired by the article :
//!     Fast computation of the Gauss hypergeometric function with all its parameters complex with application to the
//!     Poschl-Teller-Ginocchio potential wave functions by N. Michel and M.V. Stoitsov, adapted to perform SIMD calls
//!
//!  @groupheader{Example}
//!  @godbolt{doc/hypergeometric.cpp}
//======================================================================================================================
  inline constexpr auto hypergeometric = eve::functor<hypergeometric_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
