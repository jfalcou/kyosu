//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>
#include <kyosu/functions/tanh.hpp>

namespace kyosu
{
  template<typename Options> struct tan_t : eve::elementwise_callable<tan_t, Options, rad_option, radpi_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

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
  //!     // regular call
  //!     constexpr ato tan(cayley_dickson_like z)                 noexcept; //1
  //!
  //!     // semantic modifyers
  //!     constexpr auto tan[radpi](cayley_dickson_like z)         noexcept; //2
  //!     constexpr auto tan[rad](cayley_dickson_like z)           noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!      1. Returns the tangent of the argument in radian.
  //!         The behavior of this function for complex inputsis equivalent to \f$-i\tanh(i\; z)\f$.
  //!         For general cayley-dickson input,  returns \f$-I_z\, \tanh(I_z\; z)\f$ if \f$z\f$
  //!         is not zero else \f$\tan(z_0)\f$, where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
  //!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
  //!      2. Returns the tangent of the argument in \f$\pi\f$ multiples.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: complex tan](https://en.cppreference.com/w/cpp/numeric/complex/tan)
  //!   *  [Wolfram MathWorld: Tangent](https://mathworld.wolfram.com/Tangent.html)
  //!   *  [Wikipedia: tangent](https://fr.wikipedia.org/wiki/tangent)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/tan.cpp}
  //======================================================================================================================
  inline constexpr auto tan = eve::functor<tan_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu
{
  namespace _
  {
    template<typename Z, eve::callable_options O>
    KYOSU_FORCEINLINE constexpr auto tan_(KYOSU_DELAY(), O const& o, Z z) noexcept
    {
      if constexpr (concepts::real<Z>) return eve::tan[o](z);
      else if constexpr (concepts::complex<Z>)
      {
        if constexpr (!O::contains(radpi)) return mulmi(kyosu::tanh(muli(z)));
        else
        {
          auto machin = [](auto z) {
            auto [rz, iz] = z + z;
            auto [s, c] = eve::sinpicospi(iz);
            auto [sh, ch] = eve::sinhcosh(eve::pi(eve::as(rz)) * rz);
            auto tmp = c + ch;
            auto rr = eve::if_else(kyosu::is_imag(z), eve::zero, sh / tmp);
            auto ii = eve::if_else(kyosu::is_real(z), eve::zero, s / tmp);
            return kyosu::if_else(eve::is_infinite(rz), kyosu::complex(sign(rz)), kyosu::complex(rr, ii));
          };
          auto r = machin(kyosu::complex(-kyosu::imag(z), kyosu::real(z)));
          return mulmi(r);
        }
      }
      else return _::cayley_extend(kyosu::tan[o], z);
    }
  }

  inline constexpr auto tanpi = tan[radpi];
}
