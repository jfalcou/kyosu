//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/tanh.hpp>

namespace kyosu
{
  template<typename Options>
  struct coth_t : eve::elementwise_callable<coth_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(coth_t, coth_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var coth
//!   @brief Computes the hyperbolic cotangent of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T coth(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic cotangent of the argument.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Hyperbolic Cotangent](https://mathworld.wolfram.com/HyperbolicCotangent.html)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/coth.cpp}
//======================================================================================================================
  inline constexpr auto coth = eve::functor<coth_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto coth_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::coth(z);
    else if constexpr(concepts::complex<Z> )
      return kyosu::rec(kyosu::tanh(z));
    else
      return _::cayley_extend(kyosu::coth, z);
  }
}
