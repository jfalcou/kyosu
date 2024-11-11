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

namespace kyosu
{
  template<typename Options>
  struct airy_ai_t : eve::elementwise_callable<airy_ai_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::airy_ai(v); }

    KYOSU_CALLABLE_OBJECT(airy_ai_t, airy_ai_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var airy_ai
//!   @brief Computes the airy function \f$Ai\f$,
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
//!      template<eve::floating_ordered_value T> constexpr auto airy_ai(T z) noexcept;
//!
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
//!     * returns  \f$\{Ai(z)\}f$.
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

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto airy_ai_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z> )
    {
      return ai(z);
    }
    else
    {
      return cayley_extend(airy_ai, z);
    }
  }
}
