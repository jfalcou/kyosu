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
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asinpi_t : eve::elementwise_callable<asinpi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return radinpi(kyosu::asin(z)); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return (*this)(complex(v)); }

    KYOSU_CALLABLE_OBJECT(asinpi_t, asinpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asinpi
//!   @brief Computes the arc sine of the argument in \f$\pi\f$ multiples.
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
//!      template<eve::floating_ordered_value T>     constexpr auto asinpi(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto asinpi(T z) noexcept;  //2
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
//!   2. Returns `radinpi(asin(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asinpi.cpp}
//======================================================================================================================
  inline constexpr auto asinpi = eve::functor<asinpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
