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
  struct cyl_bessel_ikn_t : eve::strict_elementwise_callable<cyl_bessel_ikn_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, std::span<Z1, S> is, std::span<Z1, S> ks) const noexcept
    {   return _::cb_ikn(n, z, is, ks); }

    template<eve::integral_scalar_value Z0, typename Z1>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        auto doit = [n, z](auto is, auto ks){
          return _::cb_ikn(n, z, is, ks);
        };
        return with_alloca<Z>(eve::abs(n)+1, doit);
      }
      else
      {
        return cayley_extend_rev2(*this, n, z);
      }
    }

    KYOSU_CALLABLE_OBJECT(cyl_bessel_ikn_t, cyl_bessel_ikn_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cyl_bessel_ikn
//!   @brief Computes simultaneously the  modified Bessel functions of the first
//!   and second kind of integer orders,
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
//!      template<kyosu::concepts::cayley_dickson T constexpr auto cyl_bessel_ikn(int n, T z) noexcept;
//!      template<kyosu::concepts::complex T constexpr auto cyl_bessel_ikn(int n, T z
//!                                                       , std::span<T> js, std::span<T> ys) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_ikn(int n, T z) noexcept;
//!      template<kyosu::concepts::real T>          constexpr auto cyl_bessel_ikn(int n, T z
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
//!     * returns  a pair containing \f$I_n(z)\f$ and \f$K_n(z)\f$ and if the 'span' parameters are present
//!       ithey  must be sufficient to hold 'n+1' values each which are respectively
//!        \$(i_0(x), i_1(x), ...,  i_n(x))\f$ if 'n >= 0$ else \$(i_0(x),i_{-1}(x) ...,  i_{-n}(x)\f$ (for the same computation cost),
//!       and  \$(k_0(x), k_1(x), ...,  k_n(x))\f$ if 'n >= 0$ else \$(k_0(x),k_{-1}(x) ...,  k_{-n}(x)\f$ (for the same computation cost),
//!       but use is restricted to real or complex entries..
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cyl_bessel_ikn.cpp}
//======================================================================================================================
  inline constexpr auto cyl_bessel_ikn = eve::functor<cyl_bessel_ikn_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
