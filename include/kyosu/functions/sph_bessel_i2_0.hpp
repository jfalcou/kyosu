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
  struct sph_bessel_i2_0_t : eve::elementwise_callable<sph_bessel_i2_0_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sph_bessel_i2_0(v); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_i2_0_t, sph_bessel_i2_0_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_i2_0
//!   @brief Computes  the Bessel function,
//!   \f$ i_0^{(2)}(z) = -i y_n(iz)\f$ extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_i2_0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_i2_0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$i_0^{(2)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_i2_0.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_i2_0 = eve::functor<sph_bessel_i2_0_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_i2_0_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    ICITTE
  }
}
