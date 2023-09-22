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
  struct callable_complex
  {
    using callable_tag_type = callable_complex;

    KYOSU_DEFERS_CALLABLE(complex_);

    template<typename... T>
    KYOSU_FORCEINLINE auto operator()(T... target) const noexcept -> decltype(eve::tag_invoke(*this, target...))
    {
      return eve::tag_invoke(*this, target...);
    }

    template<typename... T>
    eve::unsupported_call<callable_complex(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var complex
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
//!      template<eve::ordered_value T> constexpr auto complex(T r, T i = 0)       noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr T complex(T z)  noexcept;
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
inline constexpr tags::callable_complex complex = {};
}
