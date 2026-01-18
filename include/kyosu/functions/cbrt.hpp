//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/nthroot.hpp>

namespace kyosu
{
  template<typename Options>
  struct cbrt_t : eve::callable<cbrt_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr auto operator()(Z const& z) const noexcept -> decltype(kyosu::nthroot[this->options()](z, real(z)))
    {
      return KYOSU_CALL(z);
    }

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr auto
    operator()(Z const& z, K const & k) const noexcept -> eve::as_wide_as_t<decltype(kyosu::nthroot[this->options()](z, real(z))), K>
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
     return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(cbrt_t, cbrt_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cbrt
//!   @brief Computes the the kth cubic  root  of the argument.
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
//!     constexpr auto cbrt(complex_like z, auto k)             noexcept;
//!     constexpr auto cbrt(complex_like z)                     noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process. floating or complex.
//!     * `k`: kth cubic root.
//!
//!   **Return value**
//!
//!     * if the first parameter is floating the call will act as if it was converted to complex before call.
//!     * the kth cubic root of z, is `exp((log(z)+2*k*i*pi)/3)`. If not present k is taken as 0.
//!
//!
//!  @groupheader{Example}
//!  @godbolt{doc/cbrt.cpp}
//======================================================================================================================
  inline constexpr auto cbrt = eve::functor<cbrt_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::value K, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cbrt_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
  {
    using e_t =  eve::element_type_t<decltype(real(z))>;
    auto kk = eve::convert(k, eve::as<e_t>());
    return kyosu::nthroot[o](z, e_t(3))*kyosu::exp_ipi(2*kk/3);
  }

  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cbrt_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    using e_t =  eve::element_type_t<decltype(real(z))>;
    return kyosu::nthroot[o](z, e_t(3));
  }
}
