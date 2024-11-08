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
  struct sph_bessel_y1_t : eve::elementwise_callable<sph_bessel_y1_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sph_bessel_y1(v); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_y1_t, sph_bessel_y1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_y1
//!   @brief Computes the spherical Bessel function of the first kind,
//!   \f$ y_1(x)= -\coz z/z^2 -\sin z/zf$
//!   extended to the complex plane and cayley_dickson values.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_y1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_y1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$y_1(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_y1.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_y1 = eve::functor<sph_bessel_y1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_y1_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_y1(z);
    }
    else
    {
      return cayley_extend(sph_bessel_y1, z);
    }
  }
}
