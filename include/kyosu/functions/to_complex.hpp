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
  struct callable_to_complex
  {
    using callable_tag_type = callable_to_complex;

    KYOSU_DEFERS_CALLABLE(to_complex_);

    template<typename... T>
    KYOSU_FORCEINLINE auto operator()(T... target) const noexcept -> decltype(eve::tag_invoke(*this, target...))
    {
      return eve::tag_invoke(*this, target...);
    }

    template<typename... T>
    eve::unsupported_call<callable_to_complex(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var to_complex
//!   @brief Constructs a kyosu::complex
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
//!      template<eve::ordered_value T> constexpr auto to_complex(T r)            noexcept;
//!      template<eve::ordered_value T> constexpr auto to_complex(T r, T i)       noexcept;

//!      template<kyosu::concepts::cayley_dickson T> constexpr T to_complex(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`       : Complex value.
//!     * `r`, `i`  : Real and imaginary part sued to construct a @ref kyosu::complex..
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::complex constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_complex.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_to_complex to_complex = {};
}

namespace kyosu::_
{
  template<eve::floating_value T>
  constexpr auto to_complex_(EVE_EXPECTS(eve::cpu_), T r)         noexcept  { return as_complex_t<T>(r, 0); }

  template<eve::floating_value T0, eve::floating_value T1>
  constexpr auto to_complex_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i)  noexcept -> as_complex_t<decltype(eve::add(r, i))>
  {
    return as_complex_t<decltype(eve::add(r, i))>{r, i};
  }

  template<concepts::complex T>
  constexpr auto to_complex_(EVE_EXPECTS(eve::cpu_), T const& v)  noexcept  { return v; }
}
