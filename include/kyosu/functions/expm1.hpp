//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct expm1_t : eve::elementwise_callable<expm1_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z> )
        return eve::expm1(z);
      else if constexpr(kyosu::concepts::complex<Z>)
      {
        auto [rz, iz] = z;
        auto [siz, ciz] = eve::sincos(iz);
        auto cosm1 = [siz, ciz](auto b) {
          return eve::if_else(abs(ciz) < eve::pio_4(eve::as(b))
                             , eve::dec(ciz), -eve::sqr(siz)/(eve::inc(ciz)));
        };
        auto r = eve::fma(eve::expm1(rz), ciz, cosm1(iz));
        auto i = eve::exp(rz)*siz;
        r = eve::if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), rz, r);
        return  complex(r, eve::if_else(kyosu::is_real(z), eve::zero, i));
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    KYOSU_CALLABLE_OBJECT(expm1_t, expm1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expm1
//!   @brief Computes the exponential of the argument minus 1.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T expm1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the expm1onential of the argument minus 1.
//!     Provisions are made to ensure good precision near zero.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/expm1.cpp}
//======================================================================================================================
  inline constexpr auto expm1 = eve::functor<expm1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
