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
  struct callable_exp: eve::elementwise
  {
    using callable_tag_type = callable_exp;

    KYOSU_DEFERS_CALLABLE(exp_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::exp(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_exp(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp
//!   @brief Computes the exponential of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr T exp(T z) noexcept; //1
//!      template<kyosu::concepts::ccomplex T>       constexpr T exp(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T exp(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns the exponential of the argument, calling `eve::exp`.
//!
//!     2. Returns the exponential of the complex input following IEEE standards:
//!
//!      * for every z: kyosu::exp(eve::conj(z)) == kyosu::conj(std::exp(z))
//!      * If z is \f$\pm0\f$, the result is \f$1\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$x+i NaN\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$+\infty+i 0\f$, the result is \f$+\infty\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite y), the result is \f$+0 \mathrm{cis}(y)\f$.
//!      * If z is \f$+\infty+i y\f$ (for any finite nonzero y), the result is \f$+\infty \mathrm{cis}(y)\f$.
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified)
//!      * If z is \f$+\infty+i \pm\infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$-\infty+i NaN\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified).
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$.
//!      * If z is \f$NaN+i y\f$ (for any nonzero y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$.
//!
//!     3.  Returns \f$e^{z_0}(\cos|\underline{z}|+\underline{z}\; \mathop{sinc}|\underline{z}|)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_exp exp = {};
}
