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
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_h2n_t : eve::strict_elementwise_callable<cyl_bessel_h2n_t, Options>
  {
    template<eve::integral_scalar_value N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return cyl_bessel_jn(n, z)-muli(cyl_bessel_yn(n, z));
      else
        return _::cayley_extend_rev(*this, n, z);
    }

    template<eve::integral_scalar_value N, concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(N n, V z) const noexcept
    {
      return eve::cyl_bessel_jn(n, z)-muli(eve::cyl_bessel_yn(n, z));
    }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h2n_t, cyl_bessel_h2n_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h2n
//!   @brief Computes the Bessel/Hankel functions of the third kind ,
//!   \f$ H_n^{(2)} =  J_n(z)-iY_n(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_h2n(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_h2n(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * return  \f$H_n^{(2)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h2n.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h2n = eve::functor<cyl_bessel_h2n_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
