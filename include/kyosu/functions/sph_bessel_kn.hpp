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
  struct sph_bessel_kn_t : eve::strict_elementwise_callable<sph_bessel_kn_t, Options>
  {
    template<eve::integral_scalar_value N, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z, std::span<Z, S> js) const noexcept
    {
      auto doit = [n, z, &js](auto ys){
        _::sb_jyn(n, z, js, ys);
      };
      with_alloca<Z>(eve::abs(n)+1, doit);
      return js[n];
    }

    template<typename N, typename Z>
    requires(eve::integral_scalar_value<N> && concepts::cayley_dickson<Z>)
    KYOSU_FORCEINLINE constexpr auto operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return _::sb_kn(n, z);
      }
      else
      {
        return _::cayley_extend_rev(*this, n, z);
      }
    }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return KYOSU_CALL(v0,complex(v1)); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_kn_t, sph_bessel_kn_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  sph_bessel_kn
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_kn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto sph_bessel_kn(int n, T z, std::span<T> js)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_kn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_kn(int n, T z, std::span<T> js)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar integral order
//!     * `z`: Value to process.
//!     * `js`:  span allocated for 'n+1' values of type 'T'
//!
//!   **Return value**
//!
//!     * returns \f$J_n(z)\f$,  and if the 'span' parameter is present it must be sufficient to hold 'n+1' values which are
//!        \f$(j_0(x), j_1(x), ...,  j_n(x))\f$ if 'n >= 0$ else \f$(j_0(x),j_{-1}(x) ...,  j_{-n}(x)\f$ (for the same computation cost),
//!        but use is restricted to real or complex entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sph_bessel_kn.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_kn = eve::functor<sph_bessel_kn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
