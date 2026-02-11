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
  template<typename Options> struct sinpi_t : eve::elementwise_callable<sinpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(sinpi_t, sinpi_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var sinpi
  //!   @brief Computes the sine of the argument in \f$\pi\f$ multiples.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr T sinpi(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the sine of the argument in \f$\pi\f$ multiples.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/sinpi.cpp}
  //======================================================================================================================
  inline constexpr auto sinpi = eve::functor<sinpi_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z sinpi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (kyosu::concepts::real<Z>) return eve::sinpi(z);
    else if constexpr (concepts::complex<Z>)
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
    else { return _::cayley_extend(kyosu::sinpi, z); }
  }
}
