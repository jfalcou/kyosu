//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/polynomial.hpp>
#include <kyosu/types/traits.hpp>

namespace kyosu::tags
{
  struct callable_right_reverse_horner: eve::elementwise
  {
    using callable_tag_type = callable_right_reverse_horner;

    KYOSU_DEFERS_CALLABLE(right_reverse_horner_);

    template < eve::floating_ordered_value ... Ts>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , Ts const &  ... vs) noexcept
    {
      return eve::reverse_horner(vs...);
    }

    template < eve::floating_ordered_value T0,  eve::floating_ordered_value ... Ts>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , T0 x, kumi::tuple<Ts...> tup) noexcept
    {
      return eve::reverse_horner(x, tup);
    }

    template < typename ... Ts>
    KYOSU_FORCEINLINE auto operator()(Ts const& ...targets) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

    template<typename... T>
    eve::unsupported_call<callable_right_reverse_horner(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}
namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var right_reverse_horner
//!   @brief Implement the right_reverse_horner scheme to evaluate polynomials
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
//!   power order,  the Right_Reverse_Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!   \f$\displaystyle p(x) = (a_0+x(...+x (a_{n-2}+ x a_{n-1})) ))\f$.\n
//!   For non commutative cases it is a right_reverse_horner scheme
//!   (the coefficients are at the right of the x powers).
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <kyosu/kyosu.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template<auto T, auto C ...>    auto right_reverse_horner(T x, C ... coefs) noexcept; //1
//!     template< auto C, eve::Range R> auto right_reverse_horner(T x, R r) noexcept;         //2
//!
//!   }
//!   @endcode
//!
//!   1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!   2. Polynom is evaluated at x the other input is a range containing the coefficients
//!
//!   **Parameters**
//!
//!     * `x` :  real or cayley-dickson argument.
//!
//!     * `coefs...` :  real or cayley-dickson arguments.
//!        The coefficients by decreasing power order
//!
//!     * `r` : Range containing The coefficients by increasing power order.
//!
//!   **Return value**
//!
//!   The value of the polynom at  `x` is returned,  according to the formula:
//!    \f$\displaystyle p(x) = (a_0+x(...+x (a_{n-2}+ x a_{n-1})) ))\f$
//!   For non commutative cases it is a right_reverse_horner scheme. See [reverse_horner](@ref reverse_horner)
//!   for the left scheme.
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
//!  @godbolt{doc/right_reverse_horner.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_right_reverse_horner right_reverse_horner = {};
}
