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
#include <kyosu/functions/to_complex.hpp>

namespace kyosu::tags
{
  struct callable_acosh: eve::elementwise
  {
    using callable_tag_type = callable_acosh;

    KYOSU_DEFERS_CALLABLE(acosh_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_acosh{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_acosh(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acosh
//!   @brief Computes the inverse hyperbolic cosine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acosh(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto acosh(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acosh(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns the complex inverse hyperbolic cosine of z, in the range of a
//!      strip unbounded along the imaginary axis and
//!      in the interval \f$[0,\pi]\f$ along the real axis.
//!
//!      * for every z: kyosu::acosh( [kyosu::conj](@ref kyosu::conj)(z)) == kyosu::conj([kyosu::acosh](@ref kyosu::acosh)(z)
//!      * If z is \f$\pm0\f$, the result is \f$+0+i\pi/2\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\infty+i\pi/2\f$
//!      * If z is \f$x+i NaN\f$ (for any finite non zero x), the result is \f$NaN+iNaN\f$.
//!      * If z is \f$i NaN\f$  the result is \f$NaN+i\pi/2\f$.
//!      * If z is \f$-\infty,y\f$ (for any positive finite y), the result is \f$+\infty,\pi\f$
//!      * If z is \f$+\infty,y\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$+\infty,3\pi/4\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN,y\f$ (for any finite y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i \infty\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!   3. Returns \f$\log(z+\sqrt{z+1}\sqrt{z-1})\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acosh.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_acosh acosh = {};
}
