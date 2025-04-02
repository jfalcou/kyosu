//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/tan.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct agd_t : eve::elementwise_callable<agd_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(agd_t, agd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var agd
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
//!     template<kyosu::concepts::cayley_dickson_like Z> constexpr complexify_t<Z> agd(Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - A real typed input z is treated as if `complex(z)` was entered.
//!     - For complex input, returns the inverse gudermanian of the argument.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Gudermannian](https://mathworld.wolfram.com/Gudermannian.html)
//!   *  [Wikipedia: Gudermannian function](https://en.wikipedia.org/wiki/Gudermannian_function)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/agd.cpp}
//======================================================================================================================
  inline constexpr auto agd = eve::functor<agd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto agd_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return kyosu::agd(complex(z));
    else if constexpr(concepts::complex<Z> )
      return kyosu::log(kyosu::tan(z*kyosu::half(as(z))+kyosu::pio_4(as(z))));
    else
      return kyosu::_::cayley_extend(kyosu::agd, z);
  }
}
