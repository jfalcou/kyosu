//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/asinh.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options>
  struct acsch_t : eve::elementwise_callable<acsch_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(acsch_t, acsch_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acsch
//!   @brief Computes the inverse hyperbolic cosecant of the argument.
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
//!     template<kyosu::concepts::cayley_dickson_like Z> constexpr complexify_t<Z> acsch(Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real type input z calls `eve::acsch(z)` and so returns the same type as input.
//!   - Returns elementwise `asinh(rec(z))`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acsch.cpp}
//======================================================================================================================
  inline constexpr auto acsch = eve::functor<acsch_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acsch_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    return kyosu::asinh(kyosu::rec(z));
  }
}
