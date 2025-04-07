//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/minus.hpp>

namespace kyosu
{
  template<typename Options>
  struct oneminus_t : eve::elementwise_callable<oneminus_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(oneminus_t, oneminus_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var oneminus
//!   @brief Computes the value one minus the argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T oneminus(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: argument.
//!
//!   **Return value**
//!
//!     Returns one minus the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/oneminus.cpp}
//======================================================================================================================
  inline constexpr auto oneminus = eve::functor<oneminus_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto oneminus_(KYOSU_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
      return eve::inc(eve::inus(z));
    else
    {
      return kyosu::inc(kyosu::minus(z));
    }
  }
}
