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
  struct rsqrt_t : eve::elementwise_callable<rsqrt_t, Options, real_only_option>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_if_t<Options, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    template<concepts::real Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    requires(Options::contains(real_only))
    {
      auto r = eve::rsqrt(z);
      return complex(r, eve::if_else(eve::is_nan(r), eve::nan, eve::zero(as(r))));
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> rsqrt(T z) noexcept;
//!
//!      // semantic modifyers
//!      template<concepts::real T> constexpr complexify_t<T> rsqrt[real_only](T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which square root is computed.
//!
//!   **Return value**
//!
//!     - A real typed input z is treated as if `complex(z)` was entered, unless the option real_only is used
//!       in which case the parameter must be a floating_value, the real part of the result will the same as an eve::rsqrt
//!       implying a Nan result if the result is not real.
//!     - Returns a square root of 1/z.
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
}
