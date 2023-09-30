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
  struct callable_tanh: eve::elementwise
  {
    using callable_tag_type = callable_tanh;

    KYOSU_DEFERS_CALLABLE(tanh_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::tanh(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_tanh(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tanh
//!   @brief Computes the hyperbolic tangent of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T tanh(T z) noexcept;
//!      template<eve::floating_ordered_value T>              constexpr T tanh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1.  Returns eve::tanh(z).
//!
//!     2. Returns elementwise the complex value
//!        of the hyperbolic tangent of the input.
//!
//!       * for every z: `kyosu::tanh(kyosu::conj(z)) == kyosu::conj(std::tanh(z))`
//!       * for every z: `kyosu::tanh(-z)           == -kyosu::tanh(z)`
//!       * If z is \f$+0\f$, the result is \f$+0\f$
//!       * If z is \f$x+i \infty\f$ (for any non zero finite x), the result is \f$NaN+i NaN\f$
//!       * If z is \f$i \infty\f$  the result is \f$i NaN\f$
//!       * If z is \f$x,NaN\f$ (for any non zero finite x), the result is \f$NaN+i NaN\f$
//!       * If z is \f$i NaN\f$  the result is \f$i NaN\f$
//!       * If z is \f$+\infty,y\f$ (for any finite positive y), the result is \f$1\f$
//!       * If z is \f$+\infty+i \infty\f$, the result is \f$1,\pm 0\f$ (the sign of the imaginary part is unspecified)
//!       * If z is \f$+\infty+i NaN\f$, the result is \f$1\f$ (the sign of the imaginary part is unspecified)
//!       * If z is \f$NaN\f$, the result is \f$NaN\f$
//!       * If z is \f$NaN+i y\f$ (for any non-zero y), the result is \f$NaN+i NaN\f$
//!       * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!     3. The call is semantically equivalent to sinh(z)/cosh(z);
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tanh.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_tanh tanh = {};
}
