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
  struct callable_horner: eve::elementwise
  {
    using callable_tag_type = callable_horner;

    KYOSU_DEFERS_CALLABLE(horner_);

    template < eve::floating_ordered_value ... Ts>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , Ts const &  ... vs) noexcept
    {
      return eve::horner(vs...);
    }

    template < eve::floating_ordered_value T0,  eve::floating_ordered_value ... Ts>
    static KYOSU_FORCEINLINE auto deferred_call(auto
                                               , T0 x, kumi::tuple<Ts...> tup) noexcept
    {
      return eve::horner(x, tup);
    }

    template < typename ... Ts>
    KYOSU_FORCEINLINE auto operator()(Ts const& ...targets) const noexcept
    -> decltype(eve::tag_invoke(*this, targets...))
    {
      return eve::tag_invoke(*this, targets...);
    }

    template<typename... T>
    eve::unsupported_call<callable_horner(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}
namespace kyosu
{
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
//! @}
//======================================================================================================================
inline constexpr tags::callable_horner horner = {};
}
