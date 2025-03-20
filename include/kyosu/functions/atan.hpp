//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/atanh.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct atan_t : eve::elementwise_callable<atan_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(eve::floating_value<Z>)
        return (*this)(complex(z));
      else if constexpr(concepts::complex<Z> )
      {
        // C99 definition here; atan(z) = -i atanh(i*z):
        auto [r, i] = z;
        auto [r1, i1] = kyosu::atanh(complex(-i, r));
        return complex(i1, -r1);
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto atan(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!    - A real typed input is treated as if `complex(z)` was entered.
//!    - For complex input, reurns the elementwise the complex principal value
//!      of the arc tangent of the input in the range of a strip unbounded along the imaginary axis
//!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
//!      Special cases are handled as if the operation was implemented by \f$-i\; \mathrm{atanh}(z\; i)\f$.
//!
//!    - For general cayley_dickson input,returns \f$ -I_z \mathrm{atanh}(z I_z)\f$ where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
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
