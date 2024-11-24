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
  struct cot_t : eve::elementwise_callable<cot_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        return kyosu::rec(kyosu::tan(z));
      }
      else
      {
        return kyosu::_::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cot(v); }

    KYOSU_CALLABLE_OBJECT(cot_t, cot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cot
//!   @brief Computes the cotangent of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T cot(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T cot(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cotangent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cot.cpp}
//======================================================================================================================
  inline constexpr auto cot = eve::functor<cot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
