//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/math.hpp>

namespace kyosu::tags
{
  struct callable_atanh : eve::elementwise
  {
    using callable_tag_type = callable_atanh;

    KYOSU_DEFERS_CALLABLE(atanh_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_atanh{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_atanh(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanh
//!   @brief Computes the atanhine of the argument.
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
//!      template<eve::ordered_value T>       constexpr auto atanh(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T> constexpr auto atanh(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if complex(z) was entered.
//!
//!   2.  Returns the complex arc hyperbolic sine of z, in the range of a half-strip mathematically
//!       unbounded along the real axis and in the interval  \f$i\times[-\pi/2, \pi/2]\f$ along
//!       the imaginary axis.
//!
//!         * for every z: eve::atanh(eve::conj(z)) == eve::conj(std::atanh(z))
//!         * for every z: eve::atanh(-z) == -eve::atanh(z)
//!         * If z is \f$+0\f$, the result is \f$+0\f$
//!         * If z is \f$NaN\f$, the result is \f$NaN\f$
//!         * If z is \f$+1\f$, the result is \f$+\infty\f$
//!         * If z is \f$x+i \infty\f$ (for any finite positive x), the result is \f$+0,\pi/2\f$
//!         * If z is \f$x+i NaN\f$ (for any finite nonzero x),  the result is \f$NaN+i NaN\f$
//!         * If z is \f$+\infty+i y\f$ (for any finite positive y),  the result is \f$i \pi/2\f$
//!         * If z is \f$+\infty+i \infty\f$, the result is \f$i \pi/2\f$
//!         * If z is \f$+\infty+i NaN\f$,  the result is \f$i NaN\f$
//!         * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!         * If z is \f$NaN+i \infty\f$, the result is \f$i \pi/2\f$ (the sign of the real part is unspecified)
//!         * If z is \f$NaN+i NaN\f$,  the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atanh.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_atanh atanh = {};
}
