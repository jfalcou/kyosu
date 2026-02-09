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
#include <kyosu/functions/horner.hpp>
#include <kyosu/types/helpers.hpp>

namespace kyosu
{
  template<typename Options>
  struct reverse_horner_t : eve::callable<reverse_horner_t, Options, eve::left_option, eve::right_option>
  {
    template<concepts::cayley_dickson_like... Zs>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<Zs...> operator()(Zs const&... zs) const noexcept
    requires(eve::same_lanes_or_scalar<Zs...>)
    {
      return KYOSU_CALL(zs...);
    }

    template<concepts::cayley_dickson_like Z, eve::non_empty_product_type Data>
    KYOSU_FORCEINLINE constexpr as_cayley_dickson_like_t<Z, coefficients<Data>> operator()(
      Z z, coefficients<Data> const& t) const noexcept
    {
      return KYOSU_CALL(z, t);
    }

    KYOSU_CALLABLE_OBJECT(reverse_horner_t, reverse_horner_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var reverse_horner
  //!   @brief Implement the reverse_horner scheme to evaluate polynomials
  //!
  //!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
  //!   power order,  the reverse Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
  //!   \f$\displaystyle p(x) = (((a_{n-1}x+a_{n-2})x+ ... )x + a_0)\f$.\n
  //!   For non commutative cases it is a left-reverse_horner scheme: coefficients are
  //!   at the left of the x powers.
  //!
  //!   using the `right` semantic modifyier allows to use a right-reverse Horner scheme:
  //!   coefficients are at the right of the x powers).
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
  //!     template< auto T, auto C ...>  auto reverse_horner(T x, C ... coefs)       noexcept; //1
  //!     template< auto C, auto K>      auto reverse_horner(T x, K tup)             noexcept; //2
  //!
  //!     Semantic modifyiers
  //!     template<auto T, auto C ...>  auto reverse_horner[left](T x, C ... coefs)  noexcept; //1
  //!     template<auto C, auto K>      auto reverse_horner[left]r(T x, K tup)       noexcept; //2
  //!     template<auto T, auto C ...>  auto reverse_horner[right](T x, C ... coefs) noexcept; //3
  //!     template<auto C, auto K>      auto reverse_horner[right]r(T x, K tup)      noexcept; //3
  //!
  //!   }
  //!   @endcode
  //!
  //!!   **Parameters**
  //!
  //!     * `x` :  real or cayley-dickson argument.
  //!
  //!     * `coefs...` :  real or cayley-dickson arguments. The coefficients by increasing power order
  //!
  //!     * `tup` : kumi tuple containing The coefficients by increasing power order.
  //!
  //!   **Return value**
  //!
  //!    1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
  //!       The value of the polynom at  `x` is returned,  according to the formula:
  //!       \f$\displaystyle p(x) = (((a_{n-1}x+a_{n-2})x+ ... )x + a_0)\f$.\n
  //!       For non commutative cases it is a left-reverse_horner scheme.
  //!    2. Polynom is evaluated at x the other input is a kumi tuple containing the coefficients
  //!    3. the right modifyier is useful only when dealing wirh cayley-dickson non commutative algebras.\n
  //!       The value of the polynom at  `x` is returned,  according to the formula:
  //!        \f$\displaystyle p(x) = (x (x (x a_{n-1}+a_{n-2})+ ... )+a_0)\f$.\n
  //!        Of course for real or complex entries left and right have no specific actions
  //!
  //!    **Notes**
  //!
  //!      If the coefficients are simd values of cardinal N, this means you simultaneously
  //!      compute the values of N polynomials.
  //!        *  If x is scalar, the polynomials are all computed at the same point
  //!        *  If x is simd, the nth polynomial is computed on the nth value of x
  //!
  //!  @groupheader{External references}
  //!   *  [Wikipedia: Horner's method](https://en.wikipedia.org/wiki/Horner%27s_method)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/reverse_horner.cpp}
  //======================================================================================================================
  inline constexpr auto reverse_horner = eve::functor<reverse_horner_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename X, eve::non_empty_product_type Data, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto reverse_horner_(KYOSU_DELAY(), O const& o, X x, coefficients<Data> const& t) noexcept
  {
    return horner[o](x, coefficients(kumi::reverse(t)));
  }

  template<typename X, typename... Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto reverse_horner_(KYOSU_DELAY(), O const& o, X xx, Zs... zs) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_like_t<X, Zs...>;
    auto x = convert(xx, eve::as_element<r_t>());
    return reverse_horner[o](x, coefficients{convert(zs, eve::as_element<r_t>())...});
  }
}
