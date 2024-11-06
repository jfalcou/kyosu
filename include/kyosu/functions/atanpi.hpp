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
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct atanpi_t : eve::elementwise_callable<atanpi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v));; }

    KYOSU_CALLABLE_OBJECT(atanpi_t, atanpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanpi
//!   @brief Computes the arc tangent of the argument in \f$\pi\f$ multiples.
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
//!      template<eve::floating_ordered_value T>     constexpr auto atanpi(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto atanpi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if [kyosu::complex](@ref kyosu::complex)(z) was entered.
//!
//!   2. Returns kyosu::radinpi([kyosu::atan](@ref kyosu::atan)(z))
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atanpi.cpp}
//======================================================================================================================
  inline constexpr auto atanpi = eve::functor<atanpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atanpi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    return kyosu::radinpi(kyosu::atan(z));
  }
}