//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>
#include <kyosu/functions/cosh.hpp>
#include <kyosu/functions/muli.hpp>

namespace kyosu
{
  template<typename Options> struct cos_t : eve::elementwise_callable<cos_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(cos_t, cos_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var cos
  //!   @brief Computes the cosine of the argument.
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
  //!      template<kyosu::concepts::cayley_dickson T> constexpr T cos(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     - Returns the cosine of the argument.
  //!     - The behavior of this function is equivalent to `kyosu::cosh(i*z)`.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference: complex cos](https://en.cppreference.com/w/cpp/numeric/complex/cos)
  //!   *  [Wolfram MathWorld: Cosine](https://mathworld.wolfram.com/Cosine.html)
  //!   *  [Wikipedia: cosinus](https://fr.wikipedia.org/wiki/cosinus)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/cos.cpp}
  //======================================================================================================================
  inline constexpr auto cos = eve::functor<cos_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O> constexpr KYOSU_FORCEINLINE Z cos_(KYOSU_DELAY(), O const&, Z const& z)
  {
    if constexpr (concepts::real<Z>) return eve::cos(z);
    else if constexpr (concepts::complex<Z>) return cosh(muli(z));
    else return _::cayley_extend(kyosu::cos, z);
  }
}
