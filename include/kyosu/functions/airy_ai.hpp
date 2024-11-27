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
  struct airy_ai_t : eve::elementwise_callable<airy_ai_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(kyosu::concepts::complex<Z> )
        return _::ai(z);
      else
        return _::cayley_extend(*this, z);
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::airy_ai(v); }

    KYOSU_CALLABLE_OBJECT(airy_ai_t, airy_ai_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var airy_ai
//!   @brief Computes the airy function \f$Ai\f$
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
//!      template<eve::floating_ordered_value T>     constexpr auto airy_ai(T z) noexcept;
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto airy_ai(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     * returns  \f$Ai(z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/airy_ai.cpp}
//======================================================================================================================
  inline constexpr auto airy_ai = eve::functor<airy_ai_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
