//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options> struct conj_t : eve::elementwise_callable<conj_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(conj_t, conj_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var conj
  //!   @brief Computes the conjugate value.
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
  //!      template<concepts::cayley_dickson T> constexpr T conj(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to conjugate.
  //!
  //!   **Return value**
  //!
  //!     Returns the conjugate of its argument. i.e. the value with the same [real](@ref kyosu::real ) part
  //!     and the opposite [pure](@ref kyosu::imag ) part.
  //!
  //!     For real inputs the call reduces to identity.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: complex conj](https://en.cppreference.com/w/cpp/numeric/complex/conj)
  //!   *  [Wolfram MathWorld: complex conjugate](https://mathworld.wolfram.com/ComplexConjugate.html)
  //!   *  [Wikipedia:complex conjugate](https://en.wikipedia.org/wiki/Complex_conjugate)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/conj.cpp}
  //======================================================================================================================

  inline constexpr auto conj = eve::functor<conj_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto conj_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return z;
    else
      return Z{kumi::map_index(
        []<typename I>(I, auto m) {
          if constexpr (I::value > 0) return -m;
          else return m;
        },
        z)};
  }
}
