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
  struct cyl_bessel_h2_1_t : eve::elementwise_callable<cyl_bessel_h2_1_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z>)
      {
        return  cyl_bessel_j1(z)-muli(cyl_bessel_y1(z));
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h2_1_t, cyl_bessel_h2_1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h2_1
//!   @brief Computes  the Bessel function of the third kind, \f$ H^{(2)}_1(x)\f$,
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_h2_1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T    cyl_bessel_h2_1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$ H^{(2)}_1(x)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h2_1.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h2_1 = eve::functor<cyl_bessel_h2_1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
