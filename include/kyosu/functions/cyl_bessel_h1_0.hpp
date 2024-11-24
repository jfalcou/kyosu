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
  struct cyl_bessel_h1_0_t : eve::elementwise_callable<cyl_bessel_h1_0_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h1_0_t, cyl_bessel_h1_0_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h1_0
//!   @brief Computes  the Bessel function of the third kind, \f$ H^{(1)}_0(x)\f$,
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_h1_0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_h1_0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$ H^{(1)}_0(x)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h1_0.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h1_0 = eve::functor<cyl_bessel_h1_0_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_h1_0_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cb_h1_0(z); //cyl_bessel_j0(z)+muli(cyl_bessel_y0(z));
    }
    else
    {
      return cayley_extend(cyl_bessel_h1_0, z);
    }
  }
}
