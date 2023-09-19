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
  struct callable_proj : eve::elementwise
  {
    using callable_tag_type = callable_proj;

    KYOSU_DEFERS_CALLABLE(proj_);

    template<eve::ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      return to_complex(v,eve::sign(v)*eve::zero(eve::as(v)));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_proj(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var proj
//!   @brief Callable object computing proj(x), the projection of the cayley_dickson number z onto the (hyper) Riemann sphere
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T proj(T z) noexcept;
//!      template<eve::ordered_value T>              constexpr T proj(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` : Value to projugate.
//!
//!   **Return value**
//!
//! For most z, std::proj(z)==z, but all infinities, even the numbers where one component
//! is infinite and the other is NaN, become positive real infinity, (inf, 0.0...) or (inf, -0.0...).
//! The sign of the pure (zero) components is the signs of the components of pure(z).
//!
//!     For floating inputs the call returns a complex number.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/proj.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_proj proj = {};
}
