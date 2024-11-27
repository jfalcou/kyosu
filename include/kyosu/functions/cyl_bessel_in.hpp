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
  struct cyl_bessel_in_t : eve::strict_elementwise_callable<cyl_bessel_in_t, Options>
  {
    template<eve::integral_scalar_value N, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::complex<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z, std::span<Z, S> js) const noexcept
    {
      auto doit = [n, z, &js](auto ys){
        _::cb_ikn(n, z, js, ys);
      };
      with_alloca<Z>(eve::abs(n)+1, doit);
      return js[n];
    }

    template<eve::integral_scalar_value N, concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr auto operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return _::cb_in(n, z);
      else
        return _::cayley_extend_rev(*this, n, z);
    }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return eve::cyl_bessel_in(v0,v1); }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_in_t, cyl_bessel_in_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  cyl_bessel_in
//!   @brief Computes the modified Bessel functions of the first kind \f$I_{n}(x)=i^{-n}J_{n }(ix)\f$,
//!   extended to the complex plane and cayley_dickson algebras.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2+n^2)y=0\f$ for which
//!   \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto cyl_bessel_in(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto cyl_bessel_in(int n, T z, std::span<T> js)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    cyl_bessel_in(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    cyl_bessel_in(int n, T z, std::span<T> js)) noexcept;
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
//!        \f$(j_0(x), j_1(x), ...,  j_n(x))\f$ if 'n >= 0$ else \f$(j_0(x),j_{-1}(x) ...,  j_{-n}(x)\f$ (for the same computation cost),
//!        but use is restricted to real or complex entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_in.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_in = eve::functor<cyl_bessel_in_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
