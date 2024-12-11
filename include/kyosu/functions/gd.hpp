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
#include <kyosu/constants/wrapped.hpp>
#include <kyosu/functions/tanh.hpp>
#include <kyosu/functions/atan.hpp>

namespace kyosu
{
  template<typename Options>
  struct gd_t : eve::elementwise_callable<gd_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return 2*kyosu::atan(tanh(z*kyosu::half(as(z))));
      else
        return kyosu::_::cayley_extend(*this, z);
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::gd(v); }

    KYOSU_CALLABLE_OBJECT(gd_t, gd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var gd
//!   @brief Computes the gudermanian of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T gd(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T gd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the gudermanian of the argument.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Gudermannian](https://mathworld.wolfram.com/Gudermannian.html)
//!   *  [Wikipedia: Gudermannian function](https://en.wikipedia.org/wiki/Gudermannian_function)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/gd.cpp}
//======================================================================================================================
  inline constexpr auto gd = eve::functor<gd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}