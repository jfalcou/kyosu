//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_polarpi.hpp>
#include <kyosu/functions/exp_ipi.hpp>

namespace kyosu
{
  template<typename Options>
  struct nthroot_t : eve::callable<nthroot_t, Options, kyosu::real_only_option>
  {
    // primary root
    template<concepts::cayley_dickson_like Z, eve::value N>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<complexify_if_t<Options, Z>, N>
    operator()(Z const& z, N const& n) const noexcept
    {
      return KYOSU_CALL(z, n);
    }

    // kth root
    template<concepts::cayley_dickson_like Z, eve::value N, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<
                                     eve::as_wide_as_t<
                                         kyosu::complexify_if_t<Options, Z>
                                     ,K>,
                                N>
    operator()(Z const& z, N const & n, K const & k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>, eve::same_lanes_or_scalar<Z, N>)
    {
      return KYOSU_CALL(z, n, k);
    }

    KYOSU_CALLABLE_OBJECT(nthroot_t, nthroot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var nthroot
//!   @brief Computes the the kth nth root  of the argument.
//!
//!   @groupheader{Header file}
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
//!     //  regular call
//!     constexpr auto nthroot(complex_like z, auto n, auto k)             noexcept;
//!     constexpr auto nthroot(complex_like z, auto n)                     noexcept;
//!
//!     // semantic modifyers
//!     constexpr auto nthroot[real_only](/*any previous overload*/)       noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process. floating or complex.
//!     * `n`: nth root
//!     * `k`: kth nth root
//!
//!   **Return value**
//!
//!     - if the first parameter is floating the call will act as if they were converted
//!       to complex before call, unless the option `real_only` is used
//!        in which case the parameter must be a floating_value,  the real part of the result will
//!        the same as an eve::nthroot and the result will be fnan if no real solution exists.
//!     - the kth nth root of z, is. `exp((log(z)+2*k*i*pi)/n)`. If not present k is taken as 0.
//!
//!  @note if the first parameter is not real the option `real_only` has no effect.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/nthroot.cpp}
//======================================================================================================================
  inline constexpr auto nthroot = eve::functor<nthroot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  //kth root
  template<typename Z, eve::value K, eve::value N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& , Z zz, N n, K k) noexcept
  {
    using e_t = eve::element_type_t<decltype(real(zz))>;
    auto nn = eve::convert(n, as<e_t>());
    auto kk = eve::convert(k, as<e_t>());
    if constexpr(concepts::complex_like<Z>)
    {
      auto z = if_else(eve::is_gtz(nn), zz, rec(zz));
      auto nnn = eve::abs(nn);
      auto [rho, theta] = kyosu::to_polarpi(z);
      auto rho_n = eve::nthroot(rho, nnn);
      return rho_n*kyosu::exp_ipi((theta+2*kk)/nnn);
    }
    else
      return cayley_extend2(nthroot, zz, nn, kk);
  }

  /// primary root
  template<typename Z, concepts::real N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& o, Z z, N n) noexcept
  requires(eve::floating_value<N>)
  {
    using e_t = eve::element_type_t<eve::as_wide_as_t<kyosu::as_real_type_t<Z>,N>>;
    if constexpr(eve::integral_value<N>)
    {
      auto nn = eve::convert(n, eve::as<e_t>());
      return nthroot(z, nn);
    }
    else if constexpr(O::contains(real_only) && concepts::real<Z>)
      return eve::nthroot[o.drop(real_only)](z, n);
    else if constexpr(concepts::real<Z>)
      return nthroot(complex(z), n);
    else
      return nthroot(z, n, zero(eve::as(real(z))));
  }

  template<typename Z, eve::integral_value N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& o, Z z, N n) noexcept
  {
    using e_t = eve::element_type_t<eve::as_wide_as_t<kyosu::as_real_type_t<Z>,N>>;
    auto nn = eve::convert(n, eve::as<e_t>());
    return nthroot(z, nn);
  }
}
