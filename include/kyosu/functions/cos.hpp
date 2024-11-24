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
#include <kyosu/functions/cosh.hpp>
#include <kyosu/functions/muli.hpp>
namespace kyosu
{
  template<typename Options>
  struct cos_t : eve::elementwise_callable<cos_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
        return cosh(muli(z));
      else
        return _::cayley_extend(*this, z);
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::cos(v); }

    KYOSU_CALLABLE_OBJECT(cos_t, cos_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cos
//!   @brief Computes the cosine of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr T cos(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T cos(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T cos(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns the cosine of the argument.
//!
//!     2. The behavior of this function is equivalent to `eve::cosh(i*z)`.
//!
//!     3.  Returns \f$\cosh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\cos(z_0)\f$, where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cos.cpp}
//======================================================================================================================
  inline constexpr auto cos = eve::functor<cos_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
