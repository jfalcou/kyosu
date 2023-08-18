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
  struct callable_kpart : eve::elementwise, extractor<3,4>
  {
    using callable_tag_type = callable_kpart;

    KYOSU_DEFERS_CALLABLE(kpart_);

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
    eve::unsupported_call<callable_kpart(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var kpart
//!   @brief Extracts the \f$k\f$  part of a value.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto& kpart(T& z)        noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto  kpart(T const& z)  noexcept;
//!      template<eve::ordered_value T>                constexpr T     kpart(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Original value.
//!
//!   **Return value**
//!
//!     Returns the \f$k\f$  part of its argument. For real and complex inputs, the call returns 0.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/kpart.cpp}
//======================================================================================================================
inline constexpr tags::callable_kpart kpart = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}
