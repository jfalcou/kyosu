//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>
#include <eve/module/bessel.hpp>

namespace kyosu::tags
{
  struct callable_airy_ai: eve::elementwise
  {
    using callable_tag_type = callable_airy_ai;

    KYOSU_DEFERS_CALLABLE(airy_ai_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept
    {
      return eve::airy_ai(v);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const & target0) const noexcept
    -> decltype(eve::tag_invoke(*this, target0))
    {
      return eve::tag_invoke(*this, target0);
    }

    template<typename... T>
    eve::unsupported_call<callable_airy_ai(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var airy_ai
//!   @brief Computes the airy function \f$Ai\f$,
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
//!      template<eve::floating_ordered_value T> constexpr auto airy_ai(T z) noexcept;
//!
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto airy_ai(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$\{Ai(z)\}f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/airy_ai.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_airy_ai airy_ai = {};
}
