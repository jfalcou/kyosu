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
  struct sph_bessel_h2n_t : eve::strict_elementwise_callable<sph_bessel_h2n_t, Options>
  {
    template<eve::integral_scalar_value N, typename Z1>
    requires( concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto  operator()(N n, Z1 const & z1) const noexcept
    { return KYOSU_CALL(n,z1); }

    template<eve::integral_scalar_value N, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(N n, V1 v1) const noexcept
    { return KYOSU_CALL(n, v1); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_h2n_t, sph_bessel_h2n_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_h2n
//!   @brief Computes the spherical Bessel/hankel functions of the third kind,
//!   \f$ h_n^{(2)}(z) = j_n(z)-iy_n(z)\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_h2n(int n, T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sph_bessel_h2n(int n, T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$h_n^{(2)}(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_h2n.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_h2n = eve::functor<sph_bessel_h2n_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_h2n_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return sb_h2n(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_h2n, n, z);
    }
  }
}