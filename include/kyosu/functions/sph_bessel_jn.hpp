//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/bessel.hpp>

namespace kyosu
{

  template<typename Options>
  struct sph_bessel_jn_t : eve::strict_elementwise_callable<sph_bessel_jn_t, Options>
  {
    template<eve::integral_scalar_value N, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z, std::span<Z, S> js) const noexcept
    { return sb_jn(n, z, js); }

    template<eve::integral_scalar_value N, concepts::cayley_dickson Z>
    //    requires(eve::integral_scalar_value<Z0> && concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return _::sb_jn(n, z);
      else
        return _::cayley_extend_rev(*this, n, z);
    }

    template<concepts::real V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return eve::sph_bessel_jn(v0,v1); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_jn_t, sph_bessel_jn_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  sph_bessel_jn
//!   @brief Computes the spherical Bessel functions of the first kind,
//!   extended to the complex plane and cayley_dickson  algebras.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_jn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto sph_bessel_jn(int n, T z, std::span<T> js)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_jn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_jn(int n, T z, std::span<T> js)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar integral positive order
//!     * `z`: Value to process.
//!     * `js`:  span of values of type 'T'
//!
//!   **Return value**
//!
//!     * returns \f$j_n(z)\f$
//!
//!   @note If the 'span' parameter is present it will contains on output values which are
//!        \f$(j_0(x), j_1(x), ...,  j_m(x))\f$ where m+1 is the minimum between n+1 and size of the span.
//!        This does not impact the computation cost, but up to now its use is restricted to real or complex entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_jn.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_jn = eve::functor<sph_bessel_jn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
