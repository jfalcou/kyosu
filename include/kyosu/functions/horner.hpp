//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/convert.hpp>
#include <kyosu/functions/fma.hpp>

namespace kyosu
{
  template<typename Options>
  struct horner_t : eve::strict_tuple_callable<horner_t, Options, eve::left_option, eve::right_option>
  {
    template<typename ...Zs>
    requires(concepts::cayley_dickson<Zs> || ...)
      KYOSU_FORCEINLINE constexpr kyosu::as_cayley_dickson_t<Zs...> operator()(Zs...zs) const noexcept

    { return KYOSU_CALL(zs...); }

    template<concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(Vs... vs) const noexcept
    { return eve::horner(vs...); }

    template<concepts::real V, concepts::real... Vs>
    KYOSU_FORCEINLINE constexpr  auto operator()(V z, kumi::tuple<Vs...> tup ) const noexcept
    { return eve::horner(z, tup); }

    template<typename Z, typename ...Zs>
    requires(concepts::cayley_dickson<Z> || (concepts::cayley_dickson<Zs> || ...))
      KYOSU_FORCEINLINE constexpr  kyosu::as_cayley_dickson_t<Z, Zs...> operator()(Z z, kumi::tuple<Zs...> tup ) const noexcept
    { return KYOSU_CALL(z, tup); }

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
//!   using the right` samantic modifyier allows to use a right-horner scheme: coefficients are at the right of the x powers).
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
//!     template< auto T, auto C ...>  auto horner(T x, C ... coefs)       noexcept;                 //1
//!     template< auto C, auto K>      auto horner(T x, K tup)             noexcept;                 //2
//!
//!     Semantic modifyiers
//!     template<auto T, auto C ...>  auto horner[left](T x, C ... coefs)  noexcept;            //1
//!     template<auto C, auto K>      auto horner[left]r(T x, K tup)       noexcept;            //2
//!     template<auto T, auto C ...>  auto horner[right](T x, C ... coefs) noexcept;            //3
//!     template<auto C, auto K>      auto horner[right]r(T x, K tup)      noexcept;            //3
//!
//!   }
//!   @endcode
//!
//!!   **Parameters**
//!
//!     * `x` :  real or cayley-dickson argument.
//!
//!     * `coefs...` :  real or cayley-dickson arguments. The coefficients by decreasing power order
//!
//!     * `tup` : kumi tuple containing The coefficients by decreasing power order.
//!
//!   **Return value**
//!
//!    1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!       The value of the polynom at  `x` is returned,  according to the formula:
//!       \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$.\n
//!       For non commutative cases it is a left-horner scheme.
//!    2. Polynom is evaluated at x the other input is a kumi tuple containing the coefficients
//!    3. the right modifyier is useful only when dealing wirh cayley-dickson non commutative algebras
//!       The value of the polynom at  `x` is returned,  according to the formula:
//!        \f$\displaystyle p(x) = (x (x (x a_0+a_1)+ ... )+a_{n-1})\f$.\n
//!        Of course for real or complex entries left and right have no specific actions
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
    constexpr size_t N = sizeof...(Zs);

    if constexpr( N == 0 ) return r_t(0);
    else if constexpr( N == 1 ) return r_t(z);
    else
    {
      r_t x = r_t(xx);
      r_t  that(z);
      if constexpr(O::contains(eve::right))
      {
        ((that = fma(x, that, r_t(zs))), ...);
      }
      else
      {
        ((that = fma(that, x, r_t(zs))), ...);
      }
      return that;
    }
  }

  template<typename X, typename ... Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto horner_(KYOSU_DELAY(), O const& o, X xx, kumi::tuple<Zs...> tup) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<Zs...>;
    r_t x = convert(xx, eve::as_element<r_t>(xx));
    return kumi::apply( [&](auto... m) { return horner[o](x, convert(m, eve::as_element<r_t>())...); }, tup);
  }

}
