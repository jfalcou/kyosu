//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/invoke.hpp>

namespace kyosu::tags
{
  struct callable_lkpart: eve::elementwise, extractor<7>
  {
    using callable_tag_type = callable_lkpart;

    KYOSU_DEFERS_CALLABLE(lkpart_);

    template<eve::floating_ordered_value T>
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
    eve::unsupported_call<callable_lkpart(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lkpart
//!   @brief Extracts the lk (eighth) part of a value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto& lkpart(T& z)        noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto  lkpart(T const& z)  noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T     lkpart(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Original value.
//!
//!   **Return value**
//!
//!     Returns the eighth part of its argument.
//!
//!     For up to quaterion inputs, the call always returns 0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lkpart.cpp}
//======================================================================================================================
inline constexpr tags::callable_lkpart lkpart = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}
