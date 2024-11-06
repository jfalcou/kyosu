//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/convert.hpp>

namespace kyosu
{
  template<typename Options>
  struct horner_t : eve::strict_elementwise_callable<horner_t, Options>
  {
    template<typename ...Zs>
    requires(concepts::cayley_dickson<Zs> || ...)
      KYOSU_FORCEINLINE constexpr auto  operator()(Zs...zs) const noexcept -> decltype((zs + ...))

    { return KYOSU_CALL(zs...); }

    template<concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(Vs... vs) const noexcept -> decltype((vs +...))
    { return eve::horner(vs...); }

    KYOSU_CALLABLE_OBJECT(horner_t, horner_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var horner
//!   @brief Implement the horner scheme to evaluate polynomials
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!   \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$.\n
//!   For non commutative cases it is a left-horner scheme: coefficients are at the left of the x powers).
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/polynomial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template<auto T, auto C ...>  auto horner(T x, C ... coefs) noexcept;  //1
//!     template< auto C, auto K> auto horner(T x, K tup) noexcept;            //2
//!
//!   }
//!   @endcode
//!
//!   1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!   2. Polynom is evaluated at x the other input is a kumi tuple containing the coefficients
//!
//!   **Parameters**
//!
//!     * `x` :  real or cayley-dickson argument.
//!
//!     * `coefs...` :  real or cayley-dickson arguments. The coefficients by decreasing power order
//!
//!     * `tup` : kumi tuple containing The coefficients by decreasing power order.
//!
//!   **Return value**
//!
//!   The value of the polynom at  `x` is returned,  according to the formula:
//!    \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$.\n
//!   For non commutative cases it is a left-horner scheme. See [right_horner](@ref right_horner)
//!   for the right scheme
//!
//!    **Notes**
//!
//!      If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/horner.cpp}
//======================================================================================================================
  inline constexpr auto horner = eve::functor<horner_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename X, typename Z, typename ... Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto horner_(KYOSU_DELAY(), O const& o, X xx, Z z, Zs... zs) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<X, Z, Zs...>;

      if constexpr( sizeof...(Zs) == 0 ) return r_t(z);
      else
      {
        auto x = r_t(xx);
        r_t  that{0};

        that = fma[o](that, x, z);
        ((that = fma[o](that, x, zs)), ...);

        return that;
      }
//    return eve::horner(kyosu::convert(zs, eve::as<r_t>())...);
  }
}
