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

    template<concepts::cayley_dickson_like Z, eve::value K>
    KYOSU_FORCEINLINE constexpr auto
    operator()(Z const& z, K const & k) const noexcept -> decltype(kyosu::nthroot(z, 3, k))
    {
     if constexpr(eve::floating_value<Z>)
         return (*this)(kyosu::complex(z), k);
      else
        return KYOSU_CALL(z, k);
    }

    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr auto
    operator()(Z const& z) const noexcept -> decltype(kyosu::nthroot(z, 3))
    {
      if constexpr(eve::floating_value<Z>)
         return (*this)(kyosu::complex(z));
      else
        return KYOSU_CALL(z);
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
//!     * if the first parameter is floating the call will act as if they were converted to complex before call.
//!     * the kth cubic root of z, is `exp((log(z)+2*k*i*pi)/3)`. If not present k is taken as 0. (k is always taken modulo 3).
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
  KYOSU_FORCEINLINE constexpr auto cbrt_(KYOSU_DELAY(), O const& , Z z, K k) noexcept
  {
    return kyosu::nthroot(z, 3, k);
  }

  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto cbrt_(KYOSU_DELAY(), O const& , Z z) noexcept
  {
    return kyosu::nthroot(z, 3, 0);
  }
}
