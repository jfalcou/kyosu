//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/acos.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct acospi_t : eve::elementwise_callable<acospi_t, Options>
  {

    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    KYOSU_CALLABLE_OBJECT(acospi_t, acospi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acospi
//!   @brief Computes the arc cosine of the argument in \f$\pi\f$ multiples.
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
//!     template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> acospi(Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!  - A real input z is treated as if `complex(z)` was entered.
//!  - Returns radinpi(acos(z))
//!
//!  @groupheader{Example}
//!  @godbolt{doc/acospi.cpp}
//======================================================================================================================
  inline constexpr auto acospi = eve::functor<acospi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acospi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    return radinpi(kyosu::acos(z));
  }
}
