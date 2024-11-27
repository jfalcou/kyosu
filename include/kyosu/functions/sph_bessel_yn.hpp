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
#include <kyosu/bessel.hpp>

namespace kyosu
{
  template<typename Options>
  struct sph_bessel_yn_t : eve::strict_elementwise_callable<sph_bessel_yn_t, Options>
  {
    template<eve::integral_scalar_value N, typename Z, std::size_t S>
    requires(eve::integral_scalar_value<N> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z, std::span<Z, S> ys) const noexcept
    {
      return sb_yn(n, z, ys);
    }

    template<eve::integral_scalar_value N, typename Z>
    requires( concepts::cayley_dickson<Z>)
    KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return _::sb_yn(n, z);
      else
        return _::cayley_extend_rev(*this, n, z);
    }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return eve::sph_bessel_yn(v0,v1); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_yn_t, sph_bessel_yn_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sph_bessel_yn
//!   @brief Computes the spherical Bessel functions of the second kind,
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_yn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto sph_bessel_yn(int n, T z, std::span<T> js)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_yn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_yn(int n, T z, std::span<T> js)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar integral order
//!     * `z`: Value to process.
//!     * `ys`: span of values of type 'T'
//!
//!   **Return value**
//!
//!     * returns \f$y_n(z)\f$.
//!
//!   @note If the 'span' parameter is present it will contains on output values which are
//!       \f$(y_0(x), y_1(x), ...,  y_m(x))\f$ where m+1 is the minimum between n+1 and size of the span.
//!        This does not impact the computation cost, but up to now its use is restricted to real or complex entries.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_yn.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_yn = eve::functor<sph_bessel_yn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
