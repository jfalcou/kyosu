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
  struct callable_proj: eve::elementwise
  {
    using callable_tag_type = callable_proj;

    KYOSU_DEFERS_CALLABLE(proj_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& v) noexcept {
      return eve::if_else(eve::is_not_finite(v), eve::inf(eve::as(v)), v);
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
//!   @brief Callable object computing proj(x), the projection of the cayley_dickson number
//!   z onto the (hyper) Riemann sphere
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
//!      template<eve::floating_ordered_value T>     constexpr T proj(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to project.
//!
//!   **Return value**
//!
//!     *  For most z, proj(z)==z, but all infinities, even the numbers where one component
//!       is infinite and the other is NaN, become positive real\n
//!       infinity, (inf, 0...) or (inf, -0...).\n
//!       The sign of the pure (zero) components are the signs of the components of pure(z).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/proj.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_proj proj = {};
}
