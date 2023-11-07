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
  struct callable_sph_bessel_k1: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_k1;

    KYOSU_DEFERS_CALLABLE(sph_bessel_k1_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& z) noexcept
    {
         auto rz = rec(z);
         return  eve::pio_2(eve::as(z))*exp(-z)*fma(rz, rz, rz);
    }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_k1(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_k1
//!   @brief Computes  the spherical Bessel function of the first kind,
//!   \f$ k_1(x)= (\pi/2) e^{-z}(1/z+1/z^2)\f$ extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_k1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_k1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$k_1(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_k1.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_k1 sph_bessel_k1 = {};
}
