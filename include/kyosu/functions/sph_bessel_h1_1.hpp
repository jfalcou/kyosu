//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct sph_bessel_h1_1_t : eve::elementwise_callable<sph_bessel_h1_1_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sph_bessel_h1_1(v); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_h1_1_t, sph_bessel_h1_1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_h1_1
//!   @brief Computes the spherical Bessel/hankel functions of the third kind,
//!   \f$ h_1^{(1)}(z) = j_1(z)+iy_1(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_h1_1(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sph_bessel_h1_1(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$h_1^{(1)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_h1_1.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_h1_1 = eve::functor<sph_bessel_h1_1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_h1_1_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    ICITTE
  }
}
