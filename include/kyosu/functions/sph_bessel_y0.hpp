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
  struct sph_bessel_y0_t : eve::elementwise_callable<sph_bessel_y0_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return _::sb_y0(z);
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sph_bessel_y0(v); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_y0_t, sph_bessel_y0_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_y0
//!   @brief Computes  the spherical Bessel function of the first kind,
//!   \f$ y_0(x)=\cos z/z \f$ extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_y0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    sph_bessel_y0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$y_0(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_y0.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_y0 = eve::functor<sph_bessel_y0_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
