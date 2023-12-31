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
  struct callable_sph_bessel_h2_1: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_h2_1;

    KYOSU_DEFERS_CALLABLE(sph_bessel_h2_1_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& z) noexcept
    {
      return complex(eve::sph_bessel_j1(z), -eve::sph_bessel_y1(z));
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target1))
    {
      return eve::tag_invoke(*this, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_h2_1(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_h2_1
//!   @brief Computes the spherical Bessel/hankel functions of the third kind,
//!   \f$ h_1^{(2)}(z) = j_1(z)-iy_1(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_h2_1(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sph_bessel_h2_1(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$h_1^{(2)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_h2_1.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_h2_1 sph_bessel_h2_1 = {};
}
