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
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/acos.hpp>


namespace kyosu
{
  template<typename Options>
  struct acosh_t : eve::elementwise_callable<acosh_t, Options>
  {
     template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    requires(!Options::contains(real_only))
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return  KYOSU_CALL(z);
    }

    template<concepts::real Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    requires(Options::contains(real_only))
    {
      auto r = eve::acosh(z);
      return complex(r, eve::if_else(eve::is_nan(r), eve::nan, eve::zero(as(r))));
    }

    KYOSU_CALLABLE_OBJECT(acosh_t, acosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acosh
//!   @brief Computes the inverse hyperbolic cosine of the argument.
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
//!     //  regular call
//!    template<concepts::cayley_dickson_like Z> constexpr complexify_t<Z> acosh(Z z) noexcept;
//!
//!     // semantic modifyers
//!     template<concepts::real Z> constexpr complexify_t<Z> acosh[real_only](Z z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!   - A real input z is treated as if `complex(z)` was entered unless the option real_only is used
//!     in which case the parameter must be a floating_value, the result will the same as an eve::acosh
//!     implying a Nan result if the result is not real.
//!   - For complex input, returns the complex inverse hyperbolic cosine of z, in the range of a
//!      strip unbounded along the imaginary axis and
//!      in the interval \f$[0,\pi]\f$ along the real axis.
//!
//!      * for every z: acosh(conj(z)) ==conj(acosh(z))
//!      * If z is \f$\pm0\f$, the result is \f$+0+i\pi/2\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\infty+i\pi/2\f$
//!      * If z is \f$x+i \textrm{NaN}\f$ (for any finite non zero x), the result is \f$\textrm{NaN}+i\textrm{NaN}\f$.
//!      * If z is \f$i \textrm{NaN}\f$  the result is \f$\textrm{NaN}+i\pi/2\f$.
//!      * If z is \f$-\infty,y\f$ (for any positive finite y), the result is \f$+\infty,\pi\f$
//!      * If z is \f$+\infty,y\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$+\infty,3\pi/4\f$
//!      * If z is \f$\pm\infty+i \textrm{NaN}\f$, the result is \f$+\infty+i \textrm{NaN}\f$
//!      * If z is \f$\textrm{NaN},y\f$ (for any finite y), the result is \f$\textrm{NaN}+i \textrm{NaN}\f$.
//!      * If z is \f$\textrm{NaN}+i \infty\f$, the result is \f$+\infty+i \textrm{NaN}\f$
//!      * If z is \f$\textrm{NaN}+i \textrm{NaN}\f$, the result is \f$\textrm{NaN}+i \textrm{NaN}\f$
//!
//!   - For general cayley_dickson input, returns \f$\log(z+\sqrt{z+1}\sqrt{z-1})\f$.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex acosh](https://en.cppreference.com/w/cpp/numeric/complex/acosh)
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Cosine](https://mathworld.wolfram.com/InverseHyperbolicCosine.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF: Inverse Hyperbolic functions](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/acosh.cpp}
//======================================================================================================================
  inline constexpr auto acosh = eve::functor<acosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto acosh_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      // acosh(a0) = +/-i acos(a0)
      // Choosing the sign of multiplier to give real(acosh(a0)) >= 0
      // we have compatibility with C99.
      auto [r, i] = kyosu::acos(z);
      auto lez = eve::is_negative(i);;
      auto res = complex(-i, r);
      res = eve::if_else(lez, res, -res);
      auto nani = eve::is_nan(i);
      if (eve::any(nani))
        return eve::if_else(nani && eve::is_finite(r)
                           , complex(eve::nan(eve::as(r)), eve::nan(eve::as(r)))
                           , res);
      else
        return res;
    }
    else
    {
      return _::cayley_extend(kyosu::acosh, z);
    }
  }
}
