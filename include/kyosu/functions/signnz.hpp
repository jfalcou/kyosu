//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/is_nez.hpp>

namespace kyosu
{
  template<typename Options>
  struct signnz_t : eve::elementwise_callable<signnz_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& c) const noexcept
    {    return kyosu::if_else(kyosu::is_nez(c), c/abs(c), Z(eve::signnz(real(c))));; }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr V operator()(V v) const noexcept
    { return eve::signnz(v); }

    KYOSU_CALLABLE_OBJECT(signnz_t, signnz_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var signnz
//!   @brief Computes tne normalized value z/abs(z) if z is not zero else the sign of the real part
//!     as a cayley_dickson.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signnzatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      template<kyosu::concepts::cayley_dickson T> constexpr T signnz(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr T signnz(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the "signnz" of the argument i.e. its normalized value,  and the sign of
//!     the real part if the input is zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/signnz.cpp}
//======================================================================================================================
  inline constexpr auto signnz = eve::functor<signnz_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
