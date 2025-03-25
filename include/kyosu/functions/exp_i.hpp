//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/muli.hpp>

namespace kyosu
{
  template<typename Options>
  struct exp_i_t : eve::elementwise_callable<exp_i_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(exp_i_t, exp_i_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp_i
//!   @brief Computes the exponential of i times the argument
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> exp_i(T z) noexcept;

//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns `exp(i*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp_i.cpp}
//======================================================================================================================
  inline constexpr auto exp_i = eve::functor<exp_i_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr Z exp_i_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z>)
    {
      auto [s, c] = eve::sincos(z);
      return  complex(c, s);
    }
    else
    {
      return kyosu::exp(muli(z));
    }
  }
}
