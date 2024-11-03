//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/details/cayleyify.hpp>

namespace kyosu
{
  template<typename Options>
  struct sinhcosh_t : eve::elementwise_callable<sinhcosh_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr kumi::tuple<Z, Z> operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr kumi::tuple<V, V> operator()(V v)
      const noexcept
    { return eve::sinhcosh(v); }

    KYOSU_CALLABLE_OBJECT(sinhcosh_t, sinhcosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinhcosh
//!   @brief Computes simultaneously  the hyperbolic sine and cosine of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sinhcosh(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sinhcosh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns simultaneously  the hyperbolic sine and cosine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinhcosh.cpp}
//======================================================================================================================
  inline constexpr auto sinhcosh = eve::functor<sinhcosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto sinhcosh_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto rs = c*sh;
      auto is = s*ch;
      auto infrz = eve::is_infinite(rz);
      auto nanrz = eve::is_nan(rz);
      if (eve::any(infrz || nanrz))
      {
        rs = eve::if_else(infrz && eve::is_not_finite(iz), rz, rs);
        is = eve::if_else(infrz && eve::is_nan(iz), eve::allbits, is);
        rs = eve::if_else(nanrz, eve::allbits, rs);
        is = eve::if_else(nanrz, eve::allbits, is);
      }
      is = eve::if_else(kyosu::is_real(z), eve::zero, is);
      rs = eve::if_else(kyosu::is_eqz(kyosu::real(z)), eve::zero, rs);
      auto ss = Z(rs, is);

      auto rc = c*ch;
      auto ic = s*sh;
      ic = eve::if_else(kyosu::is_eqz(kyosu::real(z)) || kyosu::is_real(z), eve::zero, ic);
      auto cc = Z(rc, ic);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        cc = kyosu::if_else(infrz && is_not_finite(iz), Z(eve::inf(eve::as(rz)), eve::nan(eve::as(rz))), cc);
        cc = kyosu::if_else(nanrz && is_infinite(iz),   Z(eve::nan(eve::as(rz)), eve::nan(eve::as(rz))), cc);
      }
      return kumi::tuple{ss, cc};
    }
    else
    {
      return cayley_extend2(sinhcosh, z);
    }
  }
}
