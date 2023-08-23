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
  struct callable_convert : eve::elementwise
  {
    using callable_tag_type = callable_convert;

    KYOSU_DEFERS_CALLABLE(convert_);

    template<eve::plain_scalar_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, eve::ordered_value auto const& v, eve::as<T> const& tgt) noexcept
    {
      return eve::convert(v,tgt);
    }

    template<typename T>
    KYOSU_FORCEINLINE
    auto operator()(auto const& v, eve::as<T> const& tgt) const noexcept -> decltype(eve::tag_invoke(*this,v,tgt))
    {
      return eve::tag_invoke(*this, v, tgt);
    }

    template<typename... T>
    eve::unsupported_call<callable_convert(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var convert
//!   @brief Select a value between two arguments based on a logical mask
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
//!      template<eve::value T, eve::value U, eve::value V>
//!      constexpr auto convert(T x, U, y, V z ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//!   **Return value**
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/convert.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_convert convert = {};
}
