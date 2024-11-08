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
  struct sph_bessel_jn_t : eve::strict_elementwise_callable<sph_bessel_jn_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, std::span<Z1, S> js) const noexcept
    { return KYOSU_CALL(z0,z1,js); }

    template<typename Z0, typename Z1>
    requires(eve::integral_scalar_value<Z0> || concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return KYOSU_CALL(z0,z1); }

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
//!     * `n`: scalar integral order
//!     * `z`: Value to process.
//!     * `js':  span allocated for 'n+1' values of type 'T'
//!
//!   **Return value**
//!
//!     * returns \f$J_n(z)\f$,  and if the 'span' parameter is present it must be sufficient to hold 'n+1' values which are
//!        \$(j_0(x), j_1(x), ...,  j_n(x))\f$ if 'n >= 0$ else \$(j_0(x),j_{-1}(x) ...,  j_{-n}(x)\f)$ (for the same computation cost), 
//!        but use is restricted to real or complex entries.
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

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_jn_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
     if constexpr(concepts::complex<Z> )
    {
      return sb_jn(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_jn, n, z);
    }
  }

  template<typename N, typename Z, std::size_t S, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_jn_(KYOSU_DELAY(), O const&
                                                 , N n, Z z, std::span<Z, S> js) noexcept
  {
    auto doit = [n, z, &js](auto ys){
      sb_jyn(n, z, js, ys);
    };
    with_alloca<Z>(eve::abs(n)+1, doit);
    return js[n];
  }
}
