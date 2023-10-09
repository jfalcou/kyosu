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
  struct callable_faddeeva : eve::elementwise
  {
    using callable_tag_type = callable_faddeeva;

    KYOSU_DEFERS_CALLABLE(faddeeva_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      auto fn = callable_faddeeva{};
      return fn(complex(v));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_faddeeva(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var faddeeva
//!   @brief  Callable object computing \f$e^{-z^2}\mathrm{erfc}(-iz)\f$ the scaled complex error func
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
//!      template<eve::ordered_value T>              constexpr auto faddeeva(T z) noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto faddeeva(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to process.
//!
//! **Return value**
//!
//!   Returns \f$e^{-z^2}\mathrm{erfc}(-iz)\f$ the scaled complex error function
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/faddeeva.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_faddeeva faddeeva = {};
}
