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
  struct callable_sqrt : eve::elementwise
  {
    using callable_tag_type = callable_sqrt;

    KYOSU_DEFERS_CALLABLE(sqrt_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_log{};
      return fn(kyosu::to_complex(v, T(0)));

    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sqrt(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqrt
//!   @brief Computes a square root value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T sqrt(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr T sqrt(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to for which square root is computed.
//!
//!   **Return value**
//!
//!     Returns a square root of its argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqrt.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sqrt sqrt = {};
}
