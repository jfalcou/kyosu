//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_cosh: eve::elementwise
  {
    using callable_tag_type = callable_cosh;

    KYOSU_DEFERS_CALLABLE(cosh_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::cosh(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_cosh(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cosh
//!   @brief Computes the hyperbolic cosine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr T cosh(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T cosh(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T cosh(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!   2. Returns elementwise the complex value
//!      of the hyperbolic cosine of the input.
//!
//!      * for every z: `kyosu::cosh(kyosu::conj(z)) == kyosu::conj(std::cosh(z))`
//!      * for every z: `kyosu::cosh(-z)           == kyosu::cosh(z)`
//!      *  If z is \f$0\f$, the result is \f$1\f$
//!      *  If z is \f$i \infty\f$, the result is \f$NaN\f$
//!      *  If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$x+i \infty\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$x+i NaN\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$\infty+i 0\f$, the result is \f$\infty+i 0\f$
//!      *  If z is \f$\infty,y\f$ (for any finite non-zero y), the result is \f$\infty e^{iy}\f$
//!      *  If z is \f$\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$  (the sign of the real part is unspecified)
//!      *  If z is \f$\infty+i NaN\f$, the result is \f$\infty+i NaN\f$
//!      *  If z is \f$NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$NaN+i y\f$ (for any finite non-zero y), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!   3. Is semantically equivalent to (exp(z)+exp(-z))/2.

//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cosh.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_cosh cosh = {};
}
