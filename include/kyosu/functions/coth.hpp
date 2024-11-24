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
#include <kyosu/functions/tanh.hpp>

namespace kyosu
{
  template<typename Options>
  struct coth_t : eve::elementwise_callable<coth_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return kyosu::rec(kyosu::tanh(z));
      }
      else
      {
        return kyosu::_::cayley_extend(*this, z);
      }
    }
    
    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::coth(v); }

    KYOSU_CALLABLE_OBJECT(coth_t, coth_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var coth
//!   @brief Computes the hyperbolic cotangent of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T coth(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T coth(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic cotangent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/coth.cpp}
//======================================================================================================================
  inline constexpr auto coth = eve::functor<coth_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

