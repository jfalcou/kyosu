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
  struct cyl_bessel_k0_t : eve::elementwise_callable<cyl_bessel_k0_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cyl_bessel_k0(v); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_k0_t, cyl_bessel_k0_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_k0
//!   @brief Computes  the modified Bessel function of the second kind,
//!   \f$ K_0(x)=\lim_{\alpha\to 0}{\frac {\pi }{2}}{\frac {I_{-\alpha }(x)-I_{\alpha }(x)}{\sin \alpha \pi }}\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_k0(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_k0(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$K_0(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_k0.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_k0 = eve::functor<cyl_bessel_k0_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_k0_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_k0(z);
    }
    else
    {
      return cayley_extend(cyl_bessel_k0, z);
    }
  }
}
