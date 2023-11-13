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
  struct callable_sph_bessel_h1n: eve::elementwise
  {
    using callable_tag_type = callable_sph_bessel_h1n;

    KYOSU_DEFERS_CALLABLE(sph_bessel_h1n_);

    template<eve::integral_scalar_value N, eve::floating_ordered_value T>
    static KYOSU_FORCEINLINE auto deferred_call(auto, N n, T const& z) noexcept
    {
      return complex(eve::sph_bessel_jn(n, z), eve::sph_bessel_yn(n, z));
    }

    template<typename N, typename T>
    KYOSU_FORCEINLINE auto operator()(N const & target0, T const& target1) const noexcept
    -> decltype(eve::tag_invoke(*this, target0, target1))
    {
      return eve::tag_invoke(*this, target0, target1);
    }

    template<typename... T>
    eve::unsupported_call<callable_sph_bessel_h1n(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, KYOSU_FWD(x)...); }) = delete;
  };
}

namespace kyosu
{
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_h1n
//!   @brief Computes the spherical Bessel/hankel functions of the third kind,
//!   \f$ h_n^{(1)}(z) = j_n(z)+iy_n(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_h1n(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sph_bessel_h1n(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$h_n^{(1)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_h1n.cpp}
//! @}
//======================================================================================================================
inline constexpr tags::callable_sph_bessel_h1n sph_bessel_h1n = {};
}
