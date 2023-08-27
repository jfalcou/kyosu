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
  struct callable_tanh : eve::elementwise
  {
    using callable_tag_type = callable_tanh;

    KYOSU_DEFERS_CALLABLE(tanh_);

    template<eve::ordered_value T>
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
//!      template<eve::ordered_value T>              constexpr T tanh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic tangent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tanh.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_tanh tanh = {};
}
