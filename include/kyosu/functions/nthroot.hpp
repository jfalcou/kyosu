//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_polar.hpp>
#include <kyosu/functions/exp_i.hpp>

namespace kyosu
{
  template<typename Options>
  struct nthroot_t : eve::strict_elementwise_callable<nthroot_t, Options, kyosu::real_only_option>
  {
    // primary root
    template<concepts::cayley_dickson_like Z, eve::value N>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<complexify_if_t<Options, Z>, N> operator()(Z const& z,
                                                                                             N const& n) const noexcept
    {
      return KYOSU_CALL(z, n);
    }

    // kth root
    template<concepts::cayley_dickson_like Z, eve::value N, eve::value K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z>, K>, N>
    operator()(Z const& z, N const& n, K const& k) const noexcept
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
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& o, Z zz, N n, K k) noexcept
  requires(!O::contains(real_only))
  {
    using e_t = eve::element_type_t<decltype(real(zz))>;
    auto nn = eve::convert(n, as<e_t>());
    auto kk = eve::convert(k, as<e_t>());
    if constexpr (kyosu::concepts::real<Z>) return nthroot[o](complex(zz), nn, kk);
    else if constexpr (concepts::complex_like<Z>)
    {
      auto [rho, theta] = kyosu::to_polarpi(zz);
      auto rnn = eve::rec(nn);
      auto rho_n = eve::pow_abs(rho, rnn);
      return rho_n * exp_ipi((theta + 2 * kk) * rnn);
    }
    else return cayley_extend2(nthroot, zz, nn, kk);
  }

  /// primary root
  template<typename Z, eve::floating_value N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& o, Z z, N n) noexcept
  {
    if constexpr (O::contains(real_only) && concepts::real<Z>) return eve::nthroot[o.drop(real_only)](z, n);
    else if constexpr (concepts::real<Z>) return nthroot(complex(z), n);
    else return nthroot(z, n, zero(eve::as(n)));
  }

  template<typename Z, eve::integral_value N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& o, Z z, N n) noexcept
  {
    using e_t = eve::element_type_t<kyosu::as_real_type_t<Z>>;
    auto nn = eve::convert(n, eve::as<e_t>());
    return nthroot(z, nn);
  }

  template<concepts::real Z, eve::value... K, eve::conditional_expr C, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), C const& cx, O const& o, Z z, K... k) noexcept
  {
    if constexpr (!O::contains(real_only))
      return eve::detail::mask_op(cx, eve::detail::return_2nd, complex(z), nthroot[o](z, k...));
    else return eve::detail::mask_op(cx, eve::detail::return_2nd, z, eve::nthroot[o.drop(real_only)](z, k...));
  }
}
