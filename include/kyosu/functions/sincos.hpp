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
  struct callable_sincos : eve::elementwise
  {
    using callable_tag_type = callable_sincos;

    KYOSU_DEFERS_CALLABLE(sincos_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::sincos(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sincos(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sincos
//!   @brief Computes simultaneously the sine and cosine of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sincos(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sincos(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns simultaneously  the sine and cosine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sincos.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sincos sincos = {};
}
