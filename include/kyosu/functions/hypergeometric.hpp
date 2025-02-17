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
//!
//!        Up to now the only implemented functions are for size of a and b between 0 and 2,  except \f${}_2F_0\f$ \f${}_2F_1\f$ and \f${}_2F_2\f$
//!
//!  @groupheader{Example}
//!  @godbolt{doc/hypergeometric.cpp}
//======================================================================================================================
  inline constexpr auto hypergeometric = eve::functor<hypergeometric_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
