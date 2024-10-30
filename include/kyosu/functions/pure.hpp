//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct pure_t : eve::elementwise_callable<pure_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept { return KYOSU_CALL(v); }

    KYOSU_CALLABLE_OBJECT(pure_t, pure_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pure
//!   @brief Extracts the imaginary part of a value.
//!
//!   **Defined in Header**
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T pure(T const& z)  noexcept;
//!      template<kyosu::real T>                     constexpr T pure(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Original value.
//!
//!   **Return value**
//!
//!     Returns the pure (also called imaginary) part of its argument. For real inputs, the call returns 0. It is an alias of `imag`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/imag.cpp}
//======================================================================================================================

  inline constexpr auto pure = eve::functor<pure_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto pure_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::cayley_dickson<Z>)
    {
      real(z) = 0;
      return z;
    }
    else return Z{0};
  }
}
