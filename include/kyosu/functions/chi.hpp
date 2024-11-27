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
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct chi_t : eve::elementwise_callable<chi_t, Options>
  {
    template<concepts::cayley_dickson Z, typename B>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& x, B const & b) const noexcept
    {
      auto z =  kyosu::if_else(b(x), one(as(x)), zero);
      if constexpr(Options::contains(eve::condition_key))
        return  mask_op(this->options()[eve::condition_key], eve::detail::return_2nd, x, z);
      else
        return z;
    }

    template<concepts::real V, typename B>
    KYOSU_FORCEINLINE constexpr V operator()(V v, B const & b) const noexcept
    { return eve::chi(v, b); }

    KYOSU_CALLABLE_OBJECT(chi_t, chi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var chi
//!   @brief Computes the gudermanian of the argument.
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
//!      constexpr auto chi(value auto z, auto belongs)                              noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to inspect.
//!     * `belongs`: predicate function
//!
//!   **Return value**
//!
//!     Returns 1 in the type of z if belongs(x) evaluate to true else 0.
//!
//!  @groupheader{External references}
//!   *  [wikipedia](https://en.wikipedia.org/wiki/Indicator_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/chi.cpp}
//======================================================================================================================
  inline constexpr auto chi = eve::functor<chi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
