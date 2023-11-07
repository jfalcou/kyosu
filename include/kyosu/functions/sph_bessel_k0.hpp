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
  struct callable_sph_bessel_k0: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_k0;

    KYOSU_DEFERS_CALLABLE(sph_bessel_k0_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& z) noexcept
    {
      callable_sph_bessel_k0 fn{};
      return eve::pio_2(eve::as(z))*exp(-z)/z;
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_k0(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_k0
//!   @brief Computes  the spherical Bessel function of the first kind,
//!   \f$ k_0(x)= \pi e^{-z}/(2z) \f$ extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_k0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_k0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$k_0(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_k0.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_k0 sph_bessel_k0 = {};
}
