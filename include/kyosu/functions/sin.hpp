//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
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
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sin(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     - Returns the sine of the argument.
//!     - For complex input, the behavior of this function is equivalent to \f$-i*\sinh(i*z)\f$.
//!     - For general cayley_dickson input, returns \f$-I_z\sinh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\sin(z_0)\f$,
//!       where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!        \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex sin](https://en.cppreference.com/w/cpp/numeric/complex/sin)
//!   *  [Wolfram MathWorld: Sinine](https://mathworld.wolfram.com/Sine.html)
//!   *  [Wikipedia: sinus](https://fr.wikipedia.org/wiki/sinus)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/sin.cpp}
//======================================================================================================================
  inline constexpr auto sin = eve::functor<sin_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z sin_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::real<Z>)
      return eve::sin(z);
    else if constexpr(concepts::complex<Z> )
      return kyosu::muli(kyosu::sinh(Z(kyosu::mulmi(z))));
    else
      return _::cayley_extend(kyosu::sin, z);

  }
}
