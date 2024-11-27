//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/details/cayleyify.hpp>

namespace kyosu
{
  template<typename Options>
  struct sinc_t : eve::elementwise_callable<sinc_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::complex<Z> )
      {
        auto s = kyosu::sin(z);
        using u_t = eve::underlying_type_t<Z>;
        return kyosu::if_else(kyosu::abs(z) < eve::eps(eve::as(u_t())), eve::one(eve::as(u_t())), s/z);
      }
      else
      {
        return _::cayley_extend(*this, z);
      }
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::sinc(v); }

    KYOSU_CALLABLE_OBJECT(sinc_t, sinc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinc
//!   @brief Computes the sine cardinal of the argument.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto sinc(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto sinc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the sine cardinal of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinc.cpp}
//======================================================================================================================
  inline constexpr auto sinc = eve::functor<sinc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
