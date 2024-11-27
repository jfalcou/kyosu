//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_y0_t : eve::elementwise_callable<cyl_bessel_y0_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return _::cb_y0(z);
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cyl_bessel_y0(v); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_y0_t, cyl_bessel_y0_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_y0
//!   @brief Computes  the Bessel function of the second kind,
//!   \f$ Y_0(x)=\lim_{\alpha\to 0}{{\frac {J_{\alpha  }(x)\cos(\alpha\pi)-J_{-\alpha }(x)}{\sin(\alpha\pi)}}}\f$,
//!   extended to the complex plane and cayley_dickson algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_y0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_y0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$Y_0(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_y0.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_y0 = eve::functor<cyl_bessel_y0_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
