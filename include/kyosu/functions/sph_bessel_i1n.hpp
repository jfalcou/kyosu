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
  struct sph_bessel_i1n_t : eve::strict_elementwise_callable<sph_bessel_i1n_t, Options>
  {
    template<eve::integral_scalar_value Z0, typename Z1, std::size_t S>
    requires(concepts::real<Z1> || concepts::cayley_dickson<Z1>)
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const & z1, std::span<Z1, S> js) const noexcept
    { return KYOSU_CALL(z0,z1,js); }

    template<typename Z0, typename Z1>
    requires(eve::integral_scalar_value<Z0> && concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 const& z0, Z1 const & z1) const noexcept
    { return KYOSU_CALL(z0,z1); }

    template<eve::integral_scalar_value V0, concepts::real V1>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1) const noexcept
    { return KYOSU_CALL(v0,complex(v1)); }

    KYOSU_CALLABLE_OBJECT(sph_bessel_i1n_t, sph_bessel_i1n_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  sph_bessel_i1n
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sph_bessel_i1n(int n, T z)                   noexcept;
//!      template<kyosu::concepts::complex T>        constexpr auto sph_bessel_i1n(int n, T z, std::span<T> is)  noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_i1n(int n, T z)                   noexcept;
//!      template<kyosu::concepts::real T>           constexpr T    sph_bessel_i1n(int n, T z, std::span<T> is)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar positive integral order
//!     * `z`: Value to process.
//!     * `is`:  span allocated for 'n+1' values of type 'T'.
//!
//!
//! **Return value**
//!
//!   returns \f$i^{(1)}_n(z)\f$
//!
//! @warning if the 'span' parameter is present it must be sufficient to hold \f$n+1\f$ values which are
//!   \f$(i^{(1)}_0(x), i^{(1)}_1(x), ...,  i^{(1)}_n(x))\f$ (for the same computation cost),\n
//!   but the use is then restricted to real or complex entries.\n
//!   If the span is insufficient to hold
//!   the \f$ n+1 \f$ values but say only \f$ m \lt n+1 \f$,  the call will silently return
//!   \f$ i^{(1)}_{ m-1}(z) \f$ and 'is' will only contain the \f$ m \f$ first entries.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/sph_bessel_i1n.cpp}
//======================================================================================================================
  inline constexpr auto sph_bessel_i1n = eve::functor<sph_bessel_i1n_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename N, typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_i1n_(KYOSU_DELAY(), O const&, N n, Z z) noexcept
  {
     if constexpr(concepts::complex<Z> )
    {
      return sb_i1n(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_i1n, n, z);
    }
  }

  template<typename N, typename Z, std::size_t S, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sph_bessel_i1n_(KYOSU_DELAY(), O const&
                                                 , N n, Z z, std::span<Z, S> is) noexcept
  {
    auto doit = [n, z, &is](auto ks){
      sb_jyn(n, z, is, ks);
    };
    with_alloca<Z>(eve::abs(n)+1, doit);
    return is[n];
  }
}
