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
  struct callable_asin : eve::elementwise
  {
    using callable_tag_type = callable_asin;

    KYOSU_DEFERS_CALLABLE(asin_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::asin(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_asin(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asin
//!   @brief Computes the asinine of the argument.
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
//!      template<eve::ordered_value T>       constexpr auto asin(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T> constexpr auto asin(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if to_complex(z) was entered.
//!
//!   2. Returns elementwise the complex principal value
//!      of the arc sine of the input in the range of a strip unbounded along the imaginary axis
//!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
//!
//!      special cases are handled as if the operation was implemented by \f$-i \mathrm{asinh}(i z)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asin.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_asin asin = {};
}
