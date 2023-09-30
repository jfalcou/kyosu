//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_log : eve::elementwise
  {
    using callable_tag_type = callable_log;

    KYOSU_DEFERS_CALLABLE(log_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_log{};
      return fn( kyosu::complex(v, T(0)));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_log(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log
//!   @brief Computes the natural logarithm of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr T log(T z) noexcept; //1
//!      template<kyosu::concepts::complex T> constexpr T log(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T log(T z) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!   1.  a real typed input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns elementwise the natural logarithm of the input
//!      in the range of a strip in the interval \f$i\times[-\pi, \pi]\f$ along the imaginary axis
//!      and mathematically unbounded along the real axis. .
//!
//!      * The function is continuous onto the branch cut  along the negative real axis,
//!        taking into account the sign of imaginary part
//!      * for every z: `kyosu::log(kyosu::conj(z)) == kyosu::conj(kyosu::log(z))`
//!      * If z is \f$-0\f$, the result is \f$-\infty+i \pi \f$
//!      * If z is \f$+0\f$, the result is \f$-\infty\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$+\infty+i \pi/2\f$
//!      * If z is \f$x+i NaN\f$ (for any finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite positive y), the result is \f$+\infty+i \pi \f$
//!      * If z is \f$+\infty+i y\f$ (for any finite positive y), the result is \f$+\infty\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$+\infty+i 3\pi/4\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$+\infty+i \pi/4\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!      * If z is \f$NaN+i \infty\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!   3. `log(z)` is semantically equivalent to `log(abs(z))+sign(pure(z))*arg(z)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_log log = {};
}
