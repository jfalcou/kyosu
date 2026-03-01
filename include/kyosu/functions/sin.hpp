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
  template<typename Options> struct sin_t : eve::elementwise_callable<sin_t, Options, rad_option, radpi_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
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
  //!     // regular call
  //!     constexpr auto sin(cayley_dickson_like z)         noexcept; //1
  //!
  //!     // semantic modifyers
  //!     constexpr auto sin[radpi](cayley_dickson_like z)  noexcept; //2
  //!     constexpr auto sin[rad](cayley_dickson_like z)    noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!     1. Returns the sine of the argument in radian.
  //!       - For complex arguments, the behavior of this function is equivalent to  \f$-i*\sinh(i*z)\f$.
  //!       - For general cayley_dickson input, returns \f$-I_z\sinh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\sin(z_0)\f$,
  //!         where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
  //!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
  //!     2. Returns the cosine of an argument given in \f$\pi\f$ multiples.
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

namespace kyosu
{
  namespace _
  {
    template<typename Z, eve::callable_options O>
    KYOSU_FORCEINLINE constexpr Z sin_(KYOSU_DELAY(), O const& o, Z z) noexcept
    {
      if constexpr (kyosu::concepts::real<Z>) return eve::sin[o](z);
      else if constexpr (concepts::complex<Z>)
      {
        if constexpr (!O::contains(radpi)) return kyosu::muli(kyosu::sinh(Z(kyosu::mulmi(z))));
        else
        {
          auto rz = -kyosu::imag(z);
          auto iz = kyosu::real(z);
          rz *= eve::pi(eve::as(rz));
          auto [s, c] = eve::sinpicospi(iz);
          auto [sh, ch] = eve::sinhcosh(rz);
          auto r = c * sh;
          auto i = s * ch;
          if (eve::any(kyosu::is_not_finite(z)))
          {
            r = eve::if_else(eve::is_infinite(rz) && eve::is_not_finite(iz), rz, r);
            i = eve::if_else(eve::is_infinite(rz) && eve::is_nan(iz), iz, i);
            r = eve::if_else(eve::is_nan(rz), rz, r);
            i = eve::if_else(eve::is_nan(rz), rz, i);
            i = eve::if_else(kyosu::is_imag(z), eve::zero, i);
            r = eve::if_else(kyosu::is_real(z), eve::zero, r);
          }
          return kyosu::complex(i, -r);
        }
      }
      else return _::cayley_extend(kyosu::sin[o], z);
    }
  }

  inline constexpr auto sinpi = sin[radpi];
}
