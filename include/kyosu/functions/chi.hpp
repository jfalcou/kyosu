//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/constants/wrapped.hpp>

namespace kyosu
{
  template<typename Options>
  struct chi_t : eve::strict_elementwise_callable<chi_t, Options>
  {
    template<concepts::cayley_dickson_like Z, typename B>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& x, B const & b) const noexcept
    {
      auto z = kyosu::if_else(b(x), one(as(x)), zero);
      if constexpr(Options::contains(eve::condition_key))
        return  mask_op(this->options()[eve::condition_key], eve::detail::return_2nd, x, z);
      else
        return z;
    }

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
//!      template <concepts::cayley_dickson_like Z> constexpr Z chi(Z z, auto belongs)                              noexcept;
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
//!   *  [wikipedia: indicator function](https://en.wikipedia.org/wiki/Indicator_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/chi.cpp}
//======================================================================================================================
  inline constexpr auto chi = eve::functor<chi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
