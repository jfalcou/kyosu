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
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/acsc.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct acscpi_t : eve::elementwise_callable<acscpi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr  complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(acscpi_t, acscpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acscpi
//!   @brief Computes the arc cosecant of the argume!nt in \f$\pi\f$ multiples.
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
//!      template<eve::floating_ordered_value T>     constexpr auto acscpi(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto acscpi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if `complex(z)` was entered.
//!
//!   2. Returns `radinpi(acsc(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acscpi.cpp}
//======================================================================================================================
  inline constexpr auto acscpi = eve::functor<acscpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acscpi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    returnradinpi(kyosu::acsc(z));
  }
}
