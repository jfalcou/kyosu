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
#include <kyosu/functions/sinh.hpp>
#include <kyosu/details/cayleyify.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>

namespace kyosu
{
  template<typename Options>
  struct sin_t : eve::elementwise_callable<sin_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return muli(kyosu::sinh(Z(mulmi(z))));
      else
        return _::cayley_extend(*this, z);
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sin(v); }

    KYOSU_CALLABLE_OBJECT(sin_t, sin_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sin
//!   @brief Computes the sine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto sin(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr auto sin(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sin(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns the sine of the argument.
//!
//!     2. The behavior of this function is equivalent to \f$-i*\sinh(i*z)\f$.
//!
//!     3.  Returns \f$-I_z\cosh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\sin(z_0)\f$,
//!       where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!        \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sin.cpp}
//======================================================================================================================
  inline constexpr auto sin = eve::functor<sin_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
