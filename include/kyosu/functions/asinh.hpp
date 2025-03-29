//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/details/cayleyify.hpp>
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asinh_t : eve::elementwise_callable<asinh_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(asinh_t, asinh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asinh
//!   @brief Computes the inverse hyperbolic sine of the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> asinh(T z) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real  typed input z calls eve::asinh(z) and so returns the same type as input.
//!   - For complex input, returns the complex inverse hyperbolic sine of z, with branch cuts outside the interval
//!      \f$i\times[-\pi/2, \pi/2]\f$ along the imaginary axis.
//!
//!      * for every z: `asinh(conj(z)) ==conj(asinh(z))`
//!      * for every z: `asinh(-z) == -asinh(z)`
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$\infty+i \pi/2\f$
//!      * If z is \f$x, \textrm{NaN}\f$ (for any finite x), the result is \f$ \textrm{NaN}+ i \textrm{NaN}\f$
//!      * If z is \f$\infty+ iy\f$ (for any positive finite y), the result is \f$\infty+i 0\f$
//!      * If z is \f$\infty+i \infty\f$, the result is \f$\infty+ i\pi/4\f$
//!      * If z is \f$\infty+ i \textrm{NaN}\f$, the result is \f$\infty+ i \textrm{NaN}\f$
//!      * If z is \f$ \textrm{NaN}+i 0\f$, the result is \f$ \textrm{NaN}+i 0\f$
//!      * If z is \f$ \textrm{NaN}+ iy\f$ (for any finite nonzero y), the result is \f$ \textrm{NaN}+ i \textrm{NaN}\f$
//!      * If z is \f$ \textrm{NaN}+i \infty\f$, the result is \f$\pm \infty+ i \textrm{NaN}\f$ (the sign of the real part is unspecified)
//!      * If z is \f$ \textrm{NaN}+ i \textrm{NaN}\f$, the result is \f$ \textrm{NaN}+ i \textrm{NaN}\f$
//!
//!   - For general cayley_dickson input,returns \f$\log(z+\sqrt{1+z^2})\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: asinh](https://en.cppreference.com/w/cpp/numeric/complex/asinh)
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Sine](https://mathworld.wolfram.com/InverseHyperbolicSine.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF: Inverse hyperbolic functions](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/asinh.cpp}
//======================================================================================================================
  inline constexpr auto asinh = eve::functor<asinh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto asinh_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::asinh(z);
    if constexpr(concepts::complex<Z> )
      return mulmi(kyosu::asin(muli(z)));
    else
      return kyosu::_::cayley_extend(kyosu::asinh, z);
  }
}
