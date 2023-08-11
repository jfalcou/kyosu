//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_imag : eve::elementwise
  {
    using callable_tag_type = callable_imag;

    KYOSU_DEFERS_CALLABLE(imag_);

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
    eve::unsupported_call<callable_imag(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var imag
//!   @brief Extracts the imaginary part of a value.
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
//!      template<kyosu::concepts::caley_dickinson T> constexpr auto& imag(T& z)        noexcept;
//!      template<kyosu::concepts::caley_dickinson T> constexpr auto  imag(T const& z)  noexcept;
//!      template<eve::ordered_value T>               constexpr T     imag(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Original value.
//!
//!   **Return value**
//!
//!     Returns the imaginary part of its argument. For real inputs, the call returns 0. It is an alias of `ipart`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/imag.cpp}
//======================================================================================================================
inline constexpr tags::callable_imag imag = {};

/// Alias for imag
inline constexpr tags::callable_imag ipart = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::ordered_value T> constexpr auto  imag_(EVE_EXPECTS(eve::cpu_), T const&) noexcept { return T{0}; }

  template<concepts::caley_dickinson T>
  constexpr auto imag_(EVE_EXPECTS(eve::cpu_), T const& v) noexcept { return get<1>(v); }

  template<concepts::caley_dickinson T>
  constexpr auto& imag_(EVE_EXPECTS(eve::cpu_), T&      v) noexcept { return get<1>(v); }
}
