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
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/radinpi.hpp>

namespace kyosu
{
  template<typename Options>
  struct asinpi_t : eve::elementwise_callable<asinpi_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {     if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return radinpi(kyosu::asin(z));
    }

    KYOSU_CALLABLE_OBJECT(asinpi_t, asinpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asinpi
//!   @brief Computes the arc sine of the argument in \f$\pi\f$ multiples.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr complexify_t<T> asinpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//! **Return value**
//!
//!    - A real typed input z is treated as if `complex(z)` was entered.
//!    - returns `radinpi(asin(z))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asinpi.cpp}
//======================================================================================================================
  inline constexpr auto asinpi = eve::functor<asinpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
