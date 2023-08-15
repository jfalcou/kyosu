//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_real : eve::elementwise, extractor<0,0>
  {
    using callable_tag_type = callable_real;

    KYOSU_DEFERS_CALLABLE(real_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto& deferred_call(auto, T& v) noexcept { return v; }

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return v; }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_real(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var real
//!   @brief Extracts the real part of a value.
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
//!      template<kyosu::concepts::cayley_dickinson T> constexpr auto& real(T& z)        noexcept;
//!      template<kyosu::concepts::cayley_dickinson T> constexpr auto  real(T const& z)  noexcept;
//!      template<eve::ordered_value T>                constexpr T&    real(T& z)        noexcept;
//!      template<eve::ordered_value T>                constexpr T     real(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Original value.
//!
//!   **Return value**
//!
//!     Returns the real part of its argument. For real inputs the call reduces to identity.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/real.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_real real = {};
}
