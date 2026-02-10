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
  template<typename Options> struct tan_t : eve::elementwise_callable<tan_t, Options>
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T tan(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     - returns eve::tan(z)
  //!     - For complex inputs, the behavior of this function is equivalent to \f$-i\tanh(i\; z)\f$.
  //!     - For general cayley-dickson input,  returns \f$-I_z\, \tanh(I_z\; z)\f$ if \f$z\f$ is not zero else \f$\tan(z_0)\f$, where \f$I_z = \frac{\underline{z}}{|\underline{z}|}\f$ and
  //!         \f$\underline{z}\f$ is the [pure](@ref kyosu::imag ) part of \f$z\f$.
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

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto tan_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::tan(z);
    else if constexpr (concepts::complex<Z>) return mulmi(kyosu::tanh(muli(z)));
    else return _::cayley_extend(kyosu::tan, z);
  }
}
