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
#include <kyosu/functions/atanh.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct atan_t : eve::elementwise_callable<atan_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr complex_t<V> operator()(V v) const noexcept
    { return KYOSU_CALL(complex(v)); }

    KYOSU_CALLABLE_OBJECT(atan_t, atan_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atan
//!   @brief Computes the arctangent of the argument.
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
//!      template<eve::floating_ordered_value T>     constexpr auto atan(T z) noexcept;  //1
//!      template<kyosu::concepts::complex T>        constexpr auto atan(T z) noexcept;  //2
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto atan(T z) noexcept;  //3
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
//!   2. Returns the elementwise the complex principal value
//!      of the arc tangent of the input in the range of a strip unbounded along the imaginary axis
//!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
//!      Special cases are handled as if the operation was implemented by \f$-i\; \mathrm{atanh}(z\; i)\f$.
//!
//!   3. Returns \f$ -I_z \mathrm{atanh}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
//!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: atan](https://en.cppreference.com/w/cpp/numeric/complex/atan)
//!   *  [Wolfram MathWorld: Inverse Tangent](https://mathworld.wolfram.com/InverseTangent.html)
//!   *  [Wikipedia: Inverse trigonometric functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF: Inverse trigonometric functions](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atan.cpp}
//======================================================================================================================
  inline constexpr auto atan = eve::functor<atan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto atan_(KYOSU_DELAY(), O const&, Z a0) noexcept
  {
     if constexpr(concepts::complex<Z> )
    {
      // C99 definition here; atan(a0) = -i atanh(ia0):
      auto [r, i] = a0;
      auto [r1, i1] = kyosu::atanh(complex(-i, r));
      return complex(i1, -r1);
    }
    else
    {
      return cayley_extend(atan, a0);
    }
  }
}
