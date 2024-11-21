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

namespace kyosu
{
  template<typename Options>
  struct expm1_t : eve::elementwise_callable<expm1_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::expm1(v); }

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
//!      template<kyosu::concepts::cayley_dickson T> constexpm1r T expm1(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpm1r T expm1(T z) noexcept;
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
//!
//!  @godbolt{doc/expm1.cpp}
//======================================================================================================================
  inline constexpr auto expm1 = eve::functor<expm1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto expm1_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      auto [rz, iz] = z;
      auto sc = eve::sincos(iz);
      auto siz = get<0>(sc);
      auto ciz = get<1>(sc);
      auto cosm1 = [siz, ciz](auto b) {
        return eve::if_else(abs(ciz) < eve::pio_4(eve::as(b))
                           , eve::dec(ciz), -eve::sqr(siz)/(eve::inc(ciz)));
      };
      auto r = eve::fma(expm1(rz), ciz, cosm1(iz));
      auto i = eve::exp(rz)*siz;
      r = eve::if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), rz, r);
      return  complex(r, eve::if_else(kyosu::is_real(z), eve::zero, i));
    }
    else
    {
      return cayley_extend(expm1, z);
    }
  }
}
