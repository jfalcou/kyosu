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

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_asin{};
      return fn(complex(v));
    }

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
//!   @brief Computes the arcsine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto asin(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto asin(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acos(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns the elementwise the complex principal value
//!      of the arc sine of the input in the range of a strip unbounded along the imaginary axis
//!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
//!
//!      special cases are handled as if the operation was implemented by \f$-i\; \mathrm{asinh}(z\; i)\f$
//!
//!   3. Returns \f$-I_z \mathrm{asinh}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asin.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_asin asin = {};
}
