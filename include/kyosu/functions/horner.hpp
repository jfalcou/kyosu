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
#include <tuple>

namespace kyosu
{
  template<kumi::product_type Data>
  struct coefficients : Data
  {
    coefficients(Data const& d) : Data{d} {}

    template<typename... Cs>
    coefficients(Cs const&... cs) : Data{cs...} {}
  };

  template<typename... Cs>
  coefficients(Cs const&... cs) -> coefficients<kumi::tuple<Cs...>>;
}

template<kumi::product_type Data>
struct std::tuple_size<kyosu::coefficients<Data>> : std::tuple_size<Data> {};

template<std::size_t I, kumi::product_type Data>
struct std::tuple_element<I,kyosu::coefficients<Data>> : std::tuple_element<I,Data> {};

namespace kyosu
{
  template<typename Options>
  struct horner_t : eve::callable<horner_t, Options, eve::left_option, eve::right_option>
  {
    template<concepts::cayley_dickson_like ... Zs>
    KYOSU_FORCEINLINE constexpr auto operator()(Zs const&... zs ) const noexcept
    requires(eve::same_lanes_or_scalar<Zs...>)
    {
      return KYOSU_CALL(zs...);
    }

    template<concepts::cayley_dickson_like Z, kumi::non_empty_product_type Data>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z z, coefficients<Data> const& t ) const noexcept
    {
      return KYOSU_CALL(z, t);
    }

    KYOSU_CALLABLE_OBJECT(horner_t, horner_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var horner
//!   @brief Implement the horner scheme to evaluate polynomials
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order, the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!   \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$.\n
//!   For non commutative cases it is a left-horner scheme: coefficients are at the left of the x powers.
//!
//!   using the `right` semantic modifyier allows to use a right-horner scheme: coefficients are at the right of the x powers).
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
//!     template< auto T, auto C ...>  auto horner(T x, C ... coefs)       noexcept;  //1
//!     template< auto C, auto K>      auto horner(T x, K tup)             noexcept;  //2
//!
//!     Semantic modifyiers
//!     template<auto T, auto C ...>  auto horner[left](T x, C ... coefs)  noexcept;  //1
//!     template<auto C, auto K>      auto horner[left]r(T x, K tup)       noexcept;  //2
//!     template<auto T, auto C ...>  auto horner[right](T x, C ... coefs) noexcept;  //3
//!     template<auto C, auto K>      auto horner[right]r(T x, K tup)      noexcept;  //3
//!
//!   }
//!   @endcode
//!
//!!   **Parameters**
//!
//!     * `x` :  real or cayley-dickson argument.
//!     * `coefs...` :  real or cayley-dickson arguments. The coefficients by decreasing power order
//!     * `tup` : kumi tuple containing The coefficients by decreasing power order.
//!
//!   **Return value**
//!
//!    1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!       The value of the polynom at  `x` is returned,  according to the formula:
//!       \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$.\n
//!       For non commutative cases it is a left-horner scheme.
//!    2. Polynom is evaluated at x the other input is a kumi tuple containing the coefficients
//!    3. the `right` modifyier is useful only when dealing wirh cayley-dickson non commutative algebras.\n
//!       The value of the polynom at  `x` is returned,  according to the formula:
//!        \f$\displaystyle p(x) = (x (x (x a_0+a_1)+ ... )+a_{n-1})\f$.\n
//!        Of course for real or complex entries `left` and `right` leads to the same result
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
//!  @godbolt{doc/horner.cpp}
//======================================================================================================================
  inline constexpr auto horner = eve::functor<horner_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename X, concepts::cayley_dickson_like Z, typename ... Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto horner_(KYOSU_DELAY(), O const& o, X xx, Z z, Zs... zs) noexcept
  {
    if constexpr((concepts::real<X> && ... && concepts::real<Zs>))
      return eve::horner[o](xx, zs...);
    else
    {
      using r_t = as_cayley_dickson_like_t<X, Z, Zs...>;
      constexpr size_t N = sizeof...(Zs);

      if constexpr( N == 0 ) return r_t(0);
      else if constexpr( N == 1 ) return convert(z,eve::as_element<r_t>{});
      else
      {
        r_t x = r_t(xx);
        r_t  that(z);
        if constexpr(O::contains(eve::right))
        {
          ((that = fma(x, that, convert(zs,eve::as_element<r_t>{}))), ...);
        }
        else
        {
          ((that = fma(that, x, convert(zs,eve::as_element<r_t>{}))), ...);
        }
        return that;
      }
    }
  }

  template<typename X, kumi::non_empty_product_type Data, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto horner_(KYOSU_DELAY(), O const& o, X xx, coefficients<Data> const& tup) noexcept
  {
    using r_t = as_cayley_dickson_like_t<X,Data>;
    auto x = convert(xx, eve::as_element<r_t>());
    return kumi::apply( [&](auto... m) { return horner[o](x, convert(m, eve::as_element<r_t>())...); }, tup);
  }

}
