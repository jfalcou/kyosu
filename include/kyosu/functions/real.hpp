//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_real : eve::elementwise
  {
    using callable_tag_type = callable_real;

    KYOSU_DEFERS_CALLABLE(real_);

    template<typename T>
    EVE_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename T>
    EVE_FORCEINLINE auto operator()(T& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
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
//!      template<kyosu::concepts::caley_dickinson T> constexpr auto& real(T& z)        noexcept;
//!      template<kyosu::concepts::caley_dickinson T> constexpr auto  real(T const& z)  noexcept;
//!      template<eve::ordered_value T>               constexpr T&    real(T& z)        noexcept;
//!      template<eve::ordered_value T>               constexpr T     real(T const& z)  noexcept;
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

namespace kyosu::_
{
  template<eve::ordered_value T> constexpr auto  real_(EVE_EXPECTS(eve::cpu_), T const& v) noexcept { return v; }
  template<eve::ordered_value T> constexpr auto& real_(EVE_EXPECTS(eve::cpu_), T&       v) noexcept { return v; }

  template<concepts::caley_dickinson T>
  constexpr auto real_(EVE_EXPECTS(eve::cpu_), T const& v) noexcept { return get<0>(v); }

  template<concepts::caley_dickinson T>
  constexpr auto& real_(EVE_EXPECTS(eve::cpu_), T&      v) noexcept { return get<0>(v); }
}
