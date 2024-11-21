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
#include <kyosu/functions/sinhcosh.hpp>
#include <kyosu/details/cayleyify.hpp>

namespace kyosu
{
  template<typename Options>
  struct sincos_t : eve::elementwise_callable<sincos_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr  kumi::tuple<Z, Z> operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr kumi::tuple<V, V> operator()(V v) const noexcept
    { return eve::sincos(v); }

    KYOSU_CALLABLE_OBJECT(sincos_t, sincos_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sincos
//!   @brief Computes simultaneously the sine and cosine of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sincos(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sincos(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns simultaneously  the [sine](@ref sin) and [cosine](@ref cos) of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sincos.cpp}
//======================================================================================================================
  inline constexpr auto sincos = eve::functor<sincos_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sincos_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto [sh, ch] = sinhcosh(Z(-kyosu::imag(z), kyosu::real(z)));
      return kumi::tuple{Z(kyosu::imag(sh), -kyosu::real(sh)), ch};

    }
    else
    {
      return cayley_extend2(sincos, z);
    }
  }
}
