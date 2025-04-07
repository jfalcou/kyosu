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
  struct inc_t : eve::elementwise_callable<inc_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(inc_t, inc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var inc
//!   @brief Increments the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T inc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to increment.
//!
//!   **Return value**
//!
//!     Returns  its argument plus 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/inc.cpp}
//======================================================================================================================
  inline constexpr auto inc = eve::functor<inc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto inc_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::inc(z);
    else
    {
      real(z) = eve::inc(real(z));
      return z;
    }
  }
}
