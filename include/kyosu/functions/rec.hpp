//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/if_else.hpp>
#include <kyosu/functions/is_infinite.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/functions/conj.hpp>

namespace kyosu
{
  template<typename Options>
  struct rec_t : eve::elementwise_callable<rec_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(rec_t, rec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var rec
//!   @brief Computes the inverse of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr T rec(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T rec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the inverse of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/rec.cpp}
//======================================================================================================================
  inline constexpr auto rec = eve::functor<rec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}



namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
   KYOSU_FORCEINLINE constexpr auto rec_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z> )
      return eve::rec(z);
    else
      return if_else(is_infinite(z), eve::zero, if_else(is_eqz(z), Z(eve::rec(real(z))), conj(z)/sqr_abs(z)));
  }
}
