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
  struct cyl_bessel_y1_t : eve::elementwise_callable<cyl_bessel_y1_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return _::cb_y1(z);
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cyl_bessel_y1(v); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_y1_t, cyl_bessel_y1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_y1
//!   @brief Computes  the Bessel function of the second kind,
//!   \f$ Y_1(x)=\lim_{\alpha\to 1}{{\frac {J_{\alpha  }(x)\cos(\alpha\pi)-J_{-\alpha }(x)}{\sin(\alpha\pi)}}}\f$,
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_y1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_y1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$Y_1(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_y1.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_y1 = eve::functor<cyl_bessel_y1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
