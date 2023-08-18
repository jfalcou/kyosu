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
  struct callable_ipart : eve::elementwise, extractor<1,2>
  {
    using callable_tag_type = callable_ipart;

    KYOSU_DEFERS_CALLABLE(ipart_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const&) noexcept { return T{0}; }

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
    eve::unsupported_call<callable_ipart(T&&...)> operator()(T&&... x) const
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto& ipart(T& z)        noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto  ipart(T const& z)  noexcept;
//!      template<eve::ordered_value T>                constexpr T     ipart(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Original value.
//!
//!   **Return value**
//!
//!     Returns the imaginary part of its argument. For real inputs, the call returns 0. It is an alias of `imag`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/imag.cpp}
//======================================================================================================================
inline constexpr tags::callable_ipart ipart = {};

/// Alias for ipart
inline constexpr tags::callable_ipart imag = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}
