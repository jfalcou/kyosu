//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/is_pure.hpp>
#include <kyosu/constants/fnan.hpp>

namespace kyosu
{
  template<typename Options>
  struct rsqrt_t : eve::strict_elementwise_callable<rsqrt_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }


    template<concepts::cayley_dickson_like Z, concepts::real K>
    KYOSU_FORCEINLINE constexpr eve::as_wide_as_t<kyosu::complexify_if_t<Options, Z> , K>
    operator()(Z const& z, K const & k) const noexcept
    requires(eve::same_lanes_or_scalar<Z, K>)
    {
      return KYOSU_CALL(z, k);
    }

    KYOSU_CALLABLE_OBJECT(rsqrt_t, rsqrt_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var rsqrt
//!   @brief Computes a inverse square root value.
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
//!      //  regular call
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> rsqrt(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto sqrt(T z, K k) noexcept;         //2
//!
//!      // semantic modifyers
//!      template<concepts::real T> constexpr complexify_t<T> rsqrt[real_only](T z) noexcept;             //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which square root is computed.
//!
//!   **Return value**
//!
//!     1. Returns a square root of 1/z. A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
//!       in which case the parameter must be a floating_value and the  result will the same as an eve::rsqrt
//!       implying a Nan result if the result is not real.
//!     2. Returns the kth sqrt root of z, k is taken modulo 1; 0 is identical to 1. 1 gives the opposite root.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Square Root](https://mathworld.wolfram.com/SquareRoot.html)
//!   *  [Wikipedia: Square root](https://en.wikipedia.org/wiki/Square_root)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/rsqrt.cpp}
//======================================================================================================================
  inline constexpr auto rsqrt = eve::functor<rsqrt_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto rsqrt_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(O::contains(real_only) && concepts::real<Z>)
      return eve::rsqrt[o](z);
    else
      return kyosu::rec(kyosu::sqrt[o](z));
  }

   template<concepts::cayley_dickson_like Z, concepts::real K, eve::callable_options O>
   KYOSU_FORCEINLINE constexpr auto rsqrt_(KYOSU_DELAY(), O const& o, Z z, K k) noexcept
   {
      return kyosu::rec(kyosu::sqrt[o](z, k));
  }
}
