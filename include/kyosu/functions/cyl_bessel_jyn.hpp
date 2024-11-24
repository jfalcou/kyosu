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
  struct cyl_bessel_jyn_t : eve::strict_elementwise_callable<cyl_bessel_jyn_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& n, Z1 const & z, std::span<Z1, S> js, std::span<Z1, S> ys) const noexcept
    { return _::cb_jyn(n, z, js, ys); }

    template<eve::integral_scalar_value Z0, typename Z1>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& n, Z1 const & z) const noexcept
    {
      if constexpr(concepts::complex<Z1> )
      {
        auto doit = [n, z](auto js, auto ys){
          return _::cb_jyn(n, z, js, ys);
        };
        return _::with_alloca<Z1>(eve::abs(n)+1, doit);
      }
      else
      {
        return _::cayley_extend_rev2(*this, n, z);
      }
    }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_jyn_t, cyl_bessel_jyn_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_jyn
//!   @brief Computes the simultaneous Bessel functions of the first and second kind,
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
//!      template<kyosu::concepts::cayley_dickson T constexpr auto cyl_bessel_jyn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T constexpr auto cyl_bessel_jyn(int n, T z
//!                                                       , std::span<T> js, std::span<T> ys) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_jyn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_jyn(int n, T z
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
//!     * returns  a pair containing \f$J_n(z)\f$ and \f$Y_n(z)\f$ and if the 'span' parameters are present
//!       ithey  must be sufficient to hold 'n+1' values each which are respectively
//!        \$(j_0(x), j_1(x), ...,  j_n(x))\f$ if 'n >= 0$ else \$(j_0(x),j_{-1}(x) ...,  j_{-n}(x)\f$ (for the same computation cost),
//!       and  \$(y_0(x), y_1(x), ...,  y_n(x))\f$ if 'n >= 0$ else \$(y_0(x),y_{-1}(x) ...,  y_{-n}(x)\f$ (for the same computation cost),
//!       but use is restricted to real or complex entries..
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_jyn.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_jyn = eve::functor<cyl_bessel_jyn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
