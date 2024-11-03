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
#include <kyosu/functions/tanh.hpp>

namespace kyosu
{
  template<typename Options>
  struct tan_t : eve::elementwise_callable<tan_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::tan(v); }

    KYOSU_CALLABLE_OBJECT(tan_t, tan_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tan
//!   @brief Computes the tangent of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr T tan(T z) noexcept; //1
//!      template<kyosu::concepts::complex T>        constexpr T tan(T z) noexcept; //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr T tan(T z) noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     1. Returns eve::tan(z)
//!
//!     2. The behavior of this function is equivalent to \f$-i\tanh(i\; z)\f$.
//!
//!     3. Returns \f$-I_z\,; \tanh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\tan(z_0)\f$, where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tan.cpp}
//======================================================================================================================
  inline constexpr auto tan = eve::functor<tan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto tan_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto t = kyosu::tanh(Z(-kyosu::imag(z), kyosu::real(z)));
      return Z(kyosu::imag(t), -kyosu::real(t));
    }
    else
    {
      return cayley_extend(tan, z);
    }
  }
}
