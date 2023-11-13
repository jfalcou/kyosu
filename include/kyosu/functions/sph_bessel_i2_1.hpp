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
  struct callable_sph_bessel_i2_1: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_i2_1;

    KYOSU_DEFERS_CALLABLE(sph_bessel_i2_1_);

    template<eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, T const& z) noexcept
    {
      auto [sh, ch] = eve::sinhcosh(z);
      auto rz = eve::rec(z);
      return eve::fnma(ch, rz, sh)*rz;
   }

    template<typename T>
    KYOSU_FORCEINLINE auto operator()(T const& target) const noexcept -> decltype(eve::tag_invoke(*this, target))
    {
      return eve::tag_invoke(*this, target);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_i2_1(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_i2_1
//!   @brief Computes  the Bessel function,
//!   \f$ i_1^{(2)}(z) = -y_1(iz)\f$ extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_i2_1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_i2_1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$i_1^{(2)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_i2_1.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_i2_1 sph_bessel_i2_1 = {};
}
