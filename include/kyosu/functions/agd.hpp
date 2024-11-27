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
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/tan.hpp>

namespace kyosu
{
  template<typename Options>
  struct agd_t : eve::elementwise_callable<agd_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        auto [rz, iz] = z;
        return complex(eve::atanh(eve::sin(rz)/eve::cosh(iz)), eve::atanh(eve::sinh(iz)/eve::cos(rz)));
      }
      else
      {
        return kyosu::_::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T agd(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T agd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the inverse gudermanian of the argument.
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
