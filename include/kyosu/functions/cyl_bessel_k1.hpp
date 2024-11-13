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
  struct cyl_bessel_k1_t : eve::elementwise_callable<cyl_bessel_k1_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cyl_bessel_k1(v); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_k1_t, cyl_bessel_k1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_k1
//!   @brief Computes  the Bessel function of the second kind,
//!   \f$ K_1(x)\lim_{\alpha\to 1}{\frac {\pi }{2}}{\frac {I_{-\alpha }(x)-I_{\alpha }(x)}{\sin \alpha \pi }}\f$ extended to the complex plane and cayley_dickson values.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_k1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_k1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns \f$K_1(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_k1.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_k1 = eve::functor<cyl_bessel_k1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_k1_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_k1(z);
    }
    else
    {
      return cayley_extend(cyl_bessel_k1, z);
    }
  }
}