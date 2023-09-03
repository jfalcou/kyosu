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
  struct callable_sinpicospi : eve::elementwise
  {
    using callable_tag_type = callable_sinpicospi;

    KYOSU_DEFERS_CALLABLE(sinpicospi_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept { return eve::sinpicospi(v); }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sinpicospi(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinpicospi
//!   @brief Computes simultaneously  the sine and cosine of the argument in \f$\pi\f$ mutiples.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sinpicospi(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr auto sinpicospi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!     Returns simultaneously  the sine and cosine of the argument in \f$\pi\f$ mutiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinpicospi.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sinpicospi sinpicospi = {};
}
