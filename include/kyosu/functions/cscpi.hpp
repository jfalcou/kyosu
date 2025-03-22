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
#include <kyosu/functions/sinpi.hpp>
#include <kyosu/functions/rec.hpp>


namespace kyosu
{
  template<typename Options>
  struct cscpi_t : eve::elementwise_callable<cscpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return eve::cscpi(z);
      if constexpr(concepts::complex<Z> )
        return kyosu::rec(kyosu::sinpi(z));
      else
        return _::cayley_extend(*this, z);
    }

    KYOSU_CALLABLE_OBJECT(cscpi_t, cscpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cscpi
//!   @brief Computes the cosecant from the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T cscpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cosecant from the argument in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cscpi.cpp}
//======================================================================================================================
  inline constexpr auto cscpi = eve::functor<cscpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
