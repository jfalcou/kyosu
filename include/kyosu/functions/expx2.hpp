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
#include <kyosu/functions/sqr.hpp>

namespace kyosu
{
  template<typename Options>
  struct expx2_t : eve::elementwise_callable<expx2_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(expx2_t, expx2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expx2
//!   @brief Computes the exponential of the squared argument.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T expx2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns `exp(z*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/expx2.cpp}
//======================================================================================================================
  inline constexpr auto expx2 = eve::functor<expx2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto expx2_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::real<Z> )
      return eve::expx2(z);
    else
      return exp(sqr(z));
  }
}
