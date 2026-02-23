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
#include <kyosu/functions/tan.hpp>

namespace kyosu
{
  template<typename Options> struct cot_t : eve::elementwise_callable<cot_t, Options, rad_option, radpi_option>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(cot_t, cot_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var cot
  //!   @brief Computes the cotangent of the argument.
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
  //!     constexpr auto cot(cayley_dickson_like z)                 noexcept; //1
  //!
  //!     // semantic modifyers
  //!     constexpr auto cot[radpi](cayley_dickson_like z)         noexcept; //2
  //!     constexpr auto cot[rad](cayley_dickson_like z)           noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!      1. Returns the cotangent of the argument in radian.
  //!      2. Returns the cotangent of the argument in \f$\pi\f$ multiples.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Cotangent](https://mathworld.wolfram.com/Cotangent.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/cot.cpp}
  //======================================================================================================================
  inline constexpr auto cot = eve::functor<cot_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu
{
  namespace _
  {
    template<typename Z, eve::callable_options O>
    KYOSU_FORCEINLINE constexpr auto cot_(KYOSU_DELAY(), O const& o, Z z) noexcept
    {
      if constexpr (concepts::real<Z>) return eve::cot[o](z);
      else if constexpr (concepts::complex<Z>)
      {
        if constexpr (!O::contains(radpi)) return kyosu::rec(kyosu::tan[o](z));
        else
        {
          auto r = kyosu::tanpi(z);
          r = kyosu::if_else(kyosu::is_infinite(r), eve::zero, kyosu::rec(r));
          r = kyosu::if_else(
            kyosu::is_real(z) && eve::is_flint(kyosu::real(z) * 2) && eve::is_not_flint(kyosu::real(z)), eve::zero, r);
          return kyosu::if_else(kyosu::is_real(z), kyosu::complex(kyosu::real(r)), r);
        }
      }
      else return _::cayley_extend(kyosu::cot[o], z);
    }
  }

  inline constexpr auto cotpi = cot[radpi];
}
