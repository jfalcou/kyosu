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
#include <kyosu/functions/exp_i.hpp>

namespace kyosu
{
  template<typename Options>
  struct nthroot_t : eve::callable<nthroot_t, Options, kyosu::real_only_option>
  {

    template<typename Z0,typename Z1, typename Z2>
    struct result
    {
       using type = eve::as_wide_as_t<Z0, decltype(Z1()+Z2())>;
    };

    template<eve::floating_value Z0, typename Z1,  typename Z2>
    struct result<Z0,Z1, Z2>
    {
        using type = kyosu::as_cayley_dickson_n_t<2, eve::as_wide_as_t<kyosu::as_real_type_t<Z0>, decltype(Z1()+Z2())>>;
    };

    template<typename Z0, typename Z1, typename Z2>
    using result_t = typename result<Z0, Z1, Z2>::type;

    //================================================================================

    template<concepts::cayley_dickson_like Z, eve::value N>
    KYOSU_FORCEINLINE auto
    operator()(Z const& z, N const & n) const noexcept -> result_t<Z, N, N>
    {
      if constexpr(concepts::complex<Z>)
        return KYOSU_CALL(z, n);
      else
        return (*this)(kyosu::complex(z), n);
    }

    template<concepts::cayley_dickson_like Z, eve::value N, eve::value K>
    KYOSU_FORCEINLINE constexpr auto
    operator()(Z const& z, N const & n, K const & k) const noexcept -> result_t<Z, N, K>
    {
      if constexpr(concepts::complex<Z>)
        return KYOSU_CALL(z, n, k);
      else
        return (*this)(kyosu::complex(z), n, k);
    }

    template<concepts::real Z, eve::value N>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z const& z, N const& n) const noexcept -> result_t<Z, N, N>
    requires(Options::contains(real_only))
    {
      return KYOSU_CALL(z, n);
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
//!       to complex before call, unless the option real_only is used
//!        in which case the parameter must be a floating_value,  the real part of the result will
//!        the same as an eve::nthroot and the result will be fnan if no real solution exists.
//!     - the kth nth root of z, is. `exp((log(z)+2*k*i*pi)/n)`. If not present k is taken as 0.
//!
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
  template<typename Z, eve::value N, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& , Z z, N n, K k) noexcept
  {
    using e_t = eve::element_type_t<eve::as_wide_as_t<kyosu::as_real_type_t<Z>, decltype(n+k)>>;
    auto cv = []<typename T>(T p){
      if constexpr(!eve::integral_value<T>) return p;
      else return eve::convert(p,  eve::as<e_t>());
    };
    if constexpr(concepts::complex_like<Z>)
    {
      auto [rho, theta] = kyosu::to_polarpi(z);
      auto rho_n = eve::nthroot(rho, cv(n));
      auto rntn = if_else(n == one(as(n)), z, rho_n*kyosu::exp_ipi((theta+2*cv(eve::rem(k, n)))/cv(n)));
      return rntn;
    }
    else  return  cayley_extend2(nthroot, z, n, k);
  }

  template<typename Z, eve::value N, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto nthroot_(KYOSU_DELAY(), O const& , Z z, N n) noexcept
  {
    if constexpr(O::contains(real_only))
      return kyosu::inject(eve::nthroot(z, n));
    else
      return nthroot(z, n, zero(eve::as(n)));
  }
}
