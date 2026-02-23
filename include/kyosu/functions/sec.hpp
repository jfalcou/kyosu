//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/cos.hpp>

namespace kyosu
{
  template<typename Options> struct sec_t : eve::elementwise_callable<sec_t, Options, rad_option, radpi_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(sec_t, sec_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var sec
  //!   @brief Computes the secant of the argument.
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
  //!     constexpr auto sec(cayley_dickson_like z)                 noexcept; //1
  //!
  //!     // semantic modifyers
  //!     constexpr auto sec[radpi](cayley_dickson_like z)         noexcept; //2
  //!     constexpr auto sec[rad](cayley_dickson_like z)           noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!      1. Returns the secant of the argument in radian.
  //!      2. Returns the secant of the argument in \f$\pi\f$ multiples.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Secant.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/sec.cpp}
  //======================================================================================================================
  inline constexpr auto sec = eve::functor<sec_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu
{
  namespace _
  {
    template<typename Z, eve::callable_options O>
    KYOSU_FORCEINLINE constexpr Z sec_(KYOSU_DELAY(), O const& o, Z z) noexcept
    {
      if constexpr (kyosu::concepts::real<Z>) return eve::sec[o](z);
      else if constexpr (concepts::complex<Z>) return kyosu::rec(kyosu::cos[o](z));
      else return _::cayley_extend(kyosu::sec[o], z);
    }
  }

  inline constexpr auto secpi = sec[radpi];
}
