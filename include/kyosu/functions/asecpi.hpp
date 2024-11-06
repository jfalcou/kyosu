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
#include <kyosu/functions/asec.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asecpi_t : eve::elementwise_callable<asecpi_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr  complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(asecpi_t, asecpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asecpi
//!   @brief Computes the arc secant of the argument in \f$\pi\f$ multiples.
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
//!      template<eve::floating_ordered_value T>     constexpr auto asecpi(T z) noexcept;  //1
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto asecpi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   1. a real input z is treated as if kyosu::complex(z) was entered.
//!
//!   2. Returns kyosu::radinpi([kyosu::asec](@ref kyosu::asec)(z))
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asecpi.cpp}
//======================================================================================================================
  inline constexpr auto asecpi = eve::functor<asecpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asecpi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
   return kyosu::radinpi(kyosu::asec(z));
  }
}