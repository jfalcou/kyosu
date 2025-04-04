//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/mulmi.hpp>

namespace kyosu
{
  template<typename Options>
  struct tanpi_t : eve::elementwise_callable<tanpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(tanpi_t, tanpi_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tanpi
//!   @brief Computes the tangent of the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T tanpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the tangent of the argument in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/tanpi.cpp}
//======================================================================================================================
  inline constexpr auto tanpi = eve::functor<tanpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto tanpi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::tanpi(z);
    else if constexpr(concepts::complex<Z> )
    {
      auto machin = [](auto z){
        auto [rz, iz] = z+z;
        auto [s, c] = eve::sinpicospi(iz);
        auto [sh, ch] = eve::sinhcosh(eve::pi(eve::as(rz))*rz);
        auto tmp = c+ch;
        auto rr = eve::if_else(kyosu::is_imag(z), eve::zero, sh/tmp);
        auto ii = eve::if_else(kyosu::is_real(z),eve:: zero, s/tmp);
        return kyosu::if_else(eve::is_infinite(rz), kyosu::complex(sign(rz)), kyosu::complex(rr, ii));
      };
      auto r = machin(kyosu::complex(-kyosu::imag(z), kyosu::real(z)));
      return mulmi(r);
    }
    else
    {
      return _::cayley_extend(kyosu::tanpi, z);
    }
  }
}
