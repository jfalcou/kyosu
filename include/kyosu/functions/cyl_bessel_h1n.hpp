//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct cyl_bessel_h1n_t : eve::strict_elementwise_callable<cyl_bessel_h1n_t, Options>
  {
    template<eve::integral_scalar_value N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return _::cb_jn(n, z)+muli(kyosu::cyl_bessel_yn(n, z));
      else
        return _::cayley_extend_rev(*this, n, z);
    }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 n, V1 z) const noexcept
    {
      return eve::cyl_bessel_jn(n, z)+muli(eve::cyl_bessel_yn(n, z));;
    }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h1n_t, cyl_bessel_h1n_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_h1n
//!   @brief Computes the Bessel/Hankel functions of the third kind,
//!   \f$ H_n^{(1)}(z) = J_n(z)+iY_n(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_h1n(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto cyl_bessel_h1n(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$H_n^{(1)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h1n.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h1n = eve::functor<cyl_bessel_h1n_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
