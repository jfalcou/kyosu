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
  struct callable_asinh : eve::elementwise
  {
    using callable_tag_type = callable_asinh;

    KYOSU_DEFERS_CALLABLE(asinh_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_asinh{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_asinh(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asinh
//!   @brief Computes the asinhine of the argument.
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
//!      template<eve::ordered_value T>       constexpr auto asinh(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T> constexpr auto asinh(T z) noexcept;  //2
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
//!   2. Returns the complex arc hyperbolic sine of z, with branch cuts outside the interval
//!      \f$i\times[-\pi/2, \pi/2]\f$ along the imaginary axis.
//!
//!      * for every z: eve::asinh(eve::conj(z)) == eve::conj(std::asinh(z))
//!      * for every z: eve::asinh(-z) == -eve::asinh(z)
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$+\infty+i \pi/2\f$
//!      * If z is \f$x,NaN\f$ (for any finite x), the result is \f$NaN+ iNaN\f$
//!      * If z is \f$+\infty+ iy\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$+\infty+ i\pi/4\f$
//!      * If z is \f$+\infty+ iNaN\f$, the result is \f$+\infty+ iNaN\f$
//!      * If z is \f$NaN+i 0\f$, the result is \f$NaN+i 0\f$
//!      * If z is \f$NaN+ iy\f$ (for any finite nonzero y), the result is \f$NaN+ iNaN\f$
//!      * If z is \f$NaN+i \infty\f$, the result is \f$\pm \infty+ iNaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$NaN+ iNaN\f$, the result is \f$NaN+ iNaN\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asinh.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_asinh asinh = {};
}
