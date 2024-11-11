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
  struct cyl_bessel_h12n_t : eve::strict_elementwise_callable<cyl_bessel_h12n_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, std::span<Z1, S> js, std::span<Z1, S> ys) const noexcept
    { return KYOSU_CALL(z0,z1,js,ys); }

    template<eve::integral_scalar_value Z0, typename Z1>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return KYOSU_CALL(z0,z1); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h12n_t, cyl_bessel_h12n_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_h12n
//!   @brief Computes the Hankel functions of the first and second kind,
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
//!      template<kyosu::concepts::cayley_dickson T constexpr auto cyl_bessel_h12n(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T constexpr auto cyl_bessel_h12n(int n, T z
//!                                                       , std::span<T> js, std::span<T> ys) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_h12n(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_h12n(int n, T z
//!                                                       , std::span<T> js, std::span<T> ys) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  a pair containing \f$h1n(z)\f$ and \f$h2n(z)\f$ and if the 'span' parameters are present
//!       ithey  must be sufficient to hold 'n+1' values each which are respectively
//!        \$(h1_0(x), h1_1(x), ...,  h1_n(x))\f$ if 'n >= 0$ else \$(h1_0(x),h1_{-1}(x) ...,  h1_{-n}(x)\f)$ (for the same computation cost),
//!       and  \$(h2_0(x), h2_1(x), ...,  h2_n(x))\f$ if 'n >= 0$ else \$(h2_0(x),h2_{-1}(x) ...,  h2_{-n}(x)\f)$ (for the same computation cost),
//!       but use is restricted to real or complex entries..
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h12n.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h12n = eve::functor<cyl_bessel_h12n_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{

  template<typename N, typename Z, std::size_t S, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_h12n_(KYOSU_DELAY(), O const&, N n, Z z
                                                 , std::span<Z, S> h1s, std::span<Z, S> h2s) noexcept
  {
    return cb_h12n(n, z, h1s, h2s);
  }

  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_h12n_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto doit = [n, z](auto h1s, auto h2s){
        return cb_h12n(n, z, h1s, h2s);
      };
      return with_alloca<Z>(eve::abs(n)+1, doit);
    }
    else
    {
      return caley_extend_rev2(cyl_bessel_h12n, n, z);
    }
  }
}
