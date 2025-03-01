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
    template<typename Z, kumi::product_type T1,  kumi::product_type T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(Z z, T1 a, T2 b) const noexcept
    {
      if constexpr(!Options::contains(kyosu::regularized))
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
//!     constexpr auto hypergeometric(auto z, auto a, auto b) noexcept;
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
//!     Returns the value at z of the hypergeometric function
//!     \f${}_pF_q(a_1, \dots, a_p; b_1,\dots, b_p; z) = \sum_{k = 0}^\infty \frac{(a_1)_k\dots (a_p]_k}{(b_1)_k\dots (b_q]_k}\frac{z^k}{k!}\f$.
//!     * if \f$p < q + 1\f$: the series converges absolutely for \f$z\in \mathbb{C}\f$,
//!     * if \f$p = q + 1\f$: the series converges absolutely for \f$|z| < 1\f$ and diverges for \f$|z| > 1\f$, but
//!          analytic continuation can be used to extend the computation to the whole complex plane
//!     * if \f$p > q + 1\f$: the series converges only for \f$z = 0\f$ unless the
//!          summation stops, an \f$a_i\f$ or \f$b_i\f$ being a non positive flint and the polynomial is so defined everywhere.
//!
//!     Up to now the only implemented functions are for size of a and b tuples running from 0 to 2.
//!
//!   @note hypergeometric functons are a kind of jungle. As kyosu and eve only use standard floating types as base of calculation,
//!         overflows or lack of precision along large computation can degrade the accuracy of some results.
//!         - These fonctions always return complex outputs even if entries are all real ones.
//!         - The uses of float-based inputs and computations are ok, but discouraged as overflows or lack of precision are much greater
//!           than double-based ones.
//!         - receiving a `fnan` ouput generally means than the computation did not work well.
//!         - receiving a `cnan` ouput generally means than the function is not defined here and that point is a singularity.
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
//!      and \f${}_2F_2(z, \{a_0, a_1\}, \{b_0, b_1\})\f$ are always computed using the standard serie definition.
//!   * The serie defining \f${}_2F_0(z, \{a_0, a_1\}, \{\})\f$ is generally never convergent (but at zero). the call however
//!     returns the asymptotic solution of the same differential equation verified by the formal serie,  obtained using
//!     the Tricomi function.
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
