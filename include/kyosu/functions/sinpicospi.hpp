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
  template<typename Options> struct sinpicospi_t : eve::elementwise_callable<sinpicospi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::zipped<Z, Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(sinpicospi_t, sinpicospi_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var sinpicospi
  //!   @brief Computes simultaneously  the sine and cosine of the argument in \f$\pi\f$ multiples.
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
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr eve::zipped<T, T>sinpicospi(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns simultaneously  the sine and cosine of the argument in \f$\pi\f$ multiples.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/sinpicospi.cpp}
  //======================================================================================================================
  inline constexpr auto sinpicospi = eve::functor<sinpicospi_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sinpicospi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (kyosu::concepts::real<Z>) return eve::sinpicospi(z);
    else if constexpr (concepts::complex<Z>)
    {
      auto [rz, iz] = z;
      iz *= eve::pi(eve::as(iz));
      auto [s, c] = eve::sinpicospi(rz);
      auto [sh, ch] = eve::sinhcosh(iz);
      auto rc = c * ch;
      auto ic = eve::if_else(kyosu::is_imag(z) || kyosu::is_real(z), eve::zero, -s * sh);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        rc = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::inf(eve::as(rc)), rc);
        ic = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::allbits, ic);
        rc = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, rc);
        ic = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, ic);
      }
      auto cpi = kyosu::complex(rc, ic);
      auto arz = -kyosu::imag(z);
      auto aiz = kyosu::real(z);
      arz *= eve::pi(eve::as(arz));
      auto [as, ac] = eve::sinpicospi(aiz);
      auto [ash, ach] = eve::sinhcosh(arz);
      auto rs = ac * ash;
      auto is = as * ach;
      if (eve::any(kyosu::is_not_finite(z)))
      {
        rs = eve::if_else(eve::is_infinite(aiz) && eve::is_not_finite(arz), arz, rs);
        is = eve::if_else(eve::is_infinite(aiz) && eve::is_nan(arz), iz, is);
        rs = eve::if_else(eve::is_nan(aiz), arz, rs);
        is = eve::if_else(eve::is_nan(aiz), arz, is);
        is = eve::if_else(eve::is_eqz(aiz), eve::zero, is);
        rs = eve::if_else(eve::is_eqz(arz), eve::zero, rs);
      }
      auto spi = kyosu::complex(is, -rs);
      return eve::zip(spi, cpi);
    }
    else { return _::cayley_extend2(kyosu::sinpicospi, z); }
  }
}
