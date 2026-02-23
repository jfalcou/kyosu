//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/sin.hpp>
#include <kyosu/functions/rec.hpp>

namespace kyosu
{
  template<typename Options> struct csc_t : eve::elementwise_callable<csc_t, Options, rad_option, radpi_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(csc_t, csc_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var csc
  //!   @brief Computes the cosecant of the argument.
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
  //!     constexpr auto csc(cayley_dickson_like z)                 noexcept; //1
  //!
  //!     // semantic modifyers
  //!     constexpr auto csc[radpi](cayley_dickson_like z)         noexcept; //2
  //!     constexpr auto csc[rad](cayley_dickson_like z)           noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!      1. Returns the cosecant of the argument in radian.
  //!      2. Returns the cosecant of the argument in \f$\pi\f$ multiples.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Cosecant](https://mathworld.wolfram.com/Cosecant.html)
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/csc.cpp}
  //======================================================================================================================
  inline constexpr auto csc = eve::functor<csc_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu
{
  namespace _
  {
    template<typename Z, eve::callable_options O>
    KYOSU_FORCEINLINE constexpr auto csc_(KYOSU_DELAY(), O const& o, Z z) noexcept
    {
      if constexpr (concepts::real<Z>) return eve::csc[o](z);
      else if constexpr (concepts::complex<Z>) return kyosu::rec(kyosu::sin[o](z));
      else return _::cayley_extend(kyosu::csc[o], z);
    }
  }

  inline constexpr auto cscpi = csc[radpi];
}
