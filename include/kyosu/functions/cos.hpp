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
  template<typename Options> struct cos_t : eve::elementwise_callable<cos_t, Options, rad_option, radpi_option>
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
  //!     // regular call
  //!     constexpr auto cos(cayley_dickson_like z)                 noexcept; //1
  //!
  //!     // semantic modifyers
  //!     constexpr auto cos[radpi](cayley_dickson_like z)         noexcept; //2
  //!     constexpr auto cos[rad](cayley_dickson_like z)           noexcept; //1
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!      1. Returns the cosine of the argument in radian.
  //!         The behavior of this function is equivalent to `kyosu::cosh(i*z)`.
  //!      2. Returns the cosine of the argument in \f$\pi\f$ multiples.
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

namespace kyosu
{
  namespace _
  {
    template<typename Z, eve::callable_options O>
    constexpr KYOSU_FORCEINLINE Z cos_(KYOSU_DELAY(), O const& o, Z const& z)
    {
      if constexpr (concepts::real<Z>) return eve::cos[o](z);
      else if constexpr (concepts::complex<Z>)
      {
        if constexpr (!O::contains(radpi)) return cosh(muli(z));
        else
        {
          auto [rz, iz] = z;
          iz *= eve::pi(eve::as(iz));
          auto [s, c] = eve::sinpicospi(rz);
          auto [sh, ch] = eve::sinhcosh(iz);
          auto r = c * ch;
          auto i = eve::if_else(is_imag(z) || kyosu::is_real(z), eve::zero, -s * sh);
          if (eve::any(kyosu::is_not_finite(z)))
          {
            r = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::inf(eve::as(r)), r);
            i = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::nan(eve::as(r)), i);
            r = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, r);
            i = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, i);
          }
          return kyosu::complex(r, i);
        }
      }
      else return _::cayley_extend(kyosu::cos[o], z);
    }
  }

  inline constexpr auto cospi = cos[radpi];
}
