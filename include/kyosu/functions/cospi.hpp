//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct cospi_t : eve::elementwise_callable<cospi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(cospi_t, cospi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cospi
//!   @brief Computes the cosine from the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T cospi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cosine from the argument in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cospi.cpp}
//======================================================================================================================
  inline constexpr auto cospi = eve::functor<cospi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  constexpr KYOSU_FORCEINLINE Z cospi_(KYOSU_DELAY(), O const&, Z const& z)
  {
    if constexpr(eve::floating_value<Z>)
      return eve::cospi(z);
    else if constexpr(concepts::complex<Z> )
    {
      auto [rz, iz] = z;
      iz *= eve::pi(eve::as(iz));
      auto [s, c]   = eve::sinpicospi(rz);
      auto [sh, ch] = eve::sinhcosh(iz);
      auto r = c*ch;
      auto i = eve::if_else(is_imag(z) || kyosu::is_real(z),eve::zero, -s*sh);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        r = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::inf(eve::as(r)), r);
        i = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::nan(eve::as(r)), i);
        r = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, r);
        i = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, i);
      }
      return kyosu::complex(r, i);
    }
    else
    {
      return _::cayley_extend(kyosu::cospi, z);
    }
  }
}
