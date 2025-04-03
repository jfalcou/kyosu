//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sinhcosh.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>
#include <kyosu/details/cayleyify.hpp>

namespace kyosu
{
  template<typename Options>
  struct sincos_t : eve::elementwise_callable<sincos_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::zipped<Z, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr eve::zipped<T, T> sincos(T z) noexcept;
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
    if constexpr(kyosu::concepts::real<Z>)
      return eve::sincos(z);
    else if constexpr(concepts::complex<Z> )
    {
      auto [sh, ch] = kyosu::sinhcosh(kyosu::muli(z));
      return eve::zip(kyosu::mulmi(sh), ch);

    }
    else
    {
      return _::cayley_extend2(kyosu::sincos, z);
    }
  }
}
