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
  struct cyl_bessel_h12r_t : eve::strict_elementwise_callable<cyl_bessel_h12r_t, Options>
  {
    template<concepts::real NU, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(NU const& v, Z const & z,
                                                   std::span<Z, S> js, std::span<Z, S> ys) const noexcept
    { return KYOSU_CALL(v,z,js,ys); }

    template<concepts::real NU, concepts::cayley_dickson Z>
    requires(eve::scalar_value<NU> && (concepts::real<Z> || concepts::cayley_dickson<Z>))
      KYOSU_FORCEINLINE constexpr auto  operator()(NU const& v, Z const & z) const noexcept
    { return KYOSU_CALL(v,z); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_h12r_t, cyl_bessel_h12r_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_h12r
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
//!      template<kyosu::concepts::cayley_dickson T constexpr auto cyl_bessel_h12r(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T constexpr auto cyl_bessel_h12r(int n, T z
//!                                                       , std::span<T> js, std::span<T> ys) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_h12r(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_h12r(int n, T z
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
//!        \$(h1_0(x), h1_1(x), ...,  h1_n(x))\f$ if 'n >= 0$ else \$(h1_0(x),h1_{-1}(x) ...,  h1_{-n}(x)\f$ (for the same computation cost),
//!       and  \$(h2_0(x), h2_1(x), ...,  h2_n(x))\f$ if 'n >= 0$ else \$(h2_0(x),h2_{-1}(x) ...,  h2_{-n}(x)\f$ (for the same computation cost),
//!       but use is restricted to real or complex entries..
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_h12r.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_h12r = eve::functor<cyl_bessel_h12r_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{

  template<typename N, typename Z, std::size_t S, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_h12r_(KYOSU_DELAY(), O const&, N n, Z z
                                                 , std::span<Z, S> h1s, std::span<Z, S> h2s) noexcept
  {
    return cb_h12r(n, z, h1s, h2s);
  }

  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cyl_bessel_h12r_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto doit = [n, z](auto h1s, auto h2s){
        return cb_h12r(n, z, h1s, h2s);
      };
      return with_alloca<Z>(eve::abs(n)+1, doit);
    }
    else
    {
      return caley_extend_rev2(cyl_bessel_h12r, n, z);
    }
  }
}
