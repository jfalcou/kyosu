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
  struct cyl_bessel_i0_t : eve::elementwise_callable<cyl_bessel_i0_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return _::cb_i0(z);
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cyl_bessel_i0(v); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_i0_t, cyl_bessel_i0_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_i0
//!   @brief Computes  the modified Bessel function of the first kind \f$I_{0}(x)=J_{0}(ix)\f$
//!   extended to the complex plane and cayley_dickson algebras.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+x^2y=0\f$ for which \f$ y(0) = 1\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_i0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_i0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$I_0(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_i0.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_i0 = eve::functor<cyl_bessel_i0_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
