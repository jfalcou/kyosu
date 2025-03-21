//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct atanpi_t : eve::elementwise_callable<atanpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(eve::floating_value<Z> )
        return eve::atanpi(z);
      else
        return radinpi(kyosu::atan(z)); }

    KYOSU_CALLABLE_OBJECT(atanpi_t, atanpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanpi
//!   @brief Computes the arc tangent of the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto atanpi(T z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!    - A real typed input z calls ``eve:atanpi`` so return the same type.
//!    - Returns `radinpi(atan(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atanpi.cpp}
//======================================================================================================================
  inline constexpr auto atanpi = eve::functor<atanpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
