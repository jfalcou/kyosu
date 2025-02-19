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
  struct hypergeometric_t : eve::strict_elementwise_callable<hypergeometric_t, Options>
  {
    template<typename Z, kumi::product_type T1,  kumi::product_type T2>
    constexpr KYOSU_FORCEINLINE
    auto operator()(Z z, T1 a, T2 b) const noexcept
    {

      if constexpr(concepts::real<Z>)
        return _::hyperg(kyosu::complex(z), a, b);
      else
        return _::hyperg(z, a, b);
    }
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var hypergeometric_
//!   @brief Computes the hypergeometric function \f${}_pF_q(a_1, \dots, a_p; b_1,\dots, b_p; z)\f$
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
//!        Returns the value at z of the hypergeometric function
//!        \f${}_pF_q(a_1, \dots, a_p; b_1,\dots, b_p; z) = \sum_{k = 0}^\infty \frac{(a_1)_k\dots (a_p]_k}{{(b_1)_k\dots (b_q]_k}\frac{z^k}{k!}\f$.
//!        * if \f$p < q + 1\f$: the series converges absolutely for z ∈ C,
//!        * if \f$p = q + 1\f$: the series converges absolutely for \f$|z| < 1\f$ and diverges for \f$|z| > 1\f$, but
//!          analytic continuation can be used to extend the computation to the whole complex plane
//!        * if \f$p > q + 1\f$: the series converges only for \f$z = 0\f$ unless the
//!          summation stops, an \f$a_i\f$ or \f$b_i\f$ being a non positive flint and the polynomial is so defined everywhere.
//!          However, the function has an analytic continuation  \f${}_2F_0\f$ is computed using tricomi function which itself
//!          is expressed using\f${}_1F_1\f$
//!
//!        Up to now the only implemented functions are for size of a and b between 0 and 2.
//!
//!   @note hypergeometric functons are a kind of jungle. As kyosu and eve only use standard floating types as base of calculation,
//!         overflows or lack of precision along large computation can degrade the accuracy of some results.
//!         - These fonctions always return complex outputs even if entries are all real ones.
//!         - The uses of float-based inputs and computations are ok, but discouraged as overflows or lack of precision are much greater
//!           than double-based ones.
//!         - receiving a `fnan` ouput generally means than the computation did not work well.
//!         - receiving a `cnan` ouput generally means than the function is not defined here and that is a singularity.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/hypergeometric.cpp}
//======================================================================================================================
  inline constexpr auto hypergeometric = eve::functor<hypergeometric_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
