//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options>
  struct sqr_t : eve::elementwise_callable<sqr_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr Z operator()(Z c) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return eve::sqr(c);
      else if constexpr(concepts::complex<Z>)
      {
        auto [zr, zi] = c;
        return complex((zr-zi)*(zi+zr), 2 * zr * zi);
      }
      else
      {
        auto squares = kumi::map_index([]<typename I>(I, auto const& m)
                                       { constexpr auto sgn = (I::value == 0)-(I::value > 0);
                                         return sgn*m*m; }, c);
        auto r = kumi::sum( squares, 0);
        auto a =  2*real(c);
        real(c) = 0;
        return r+a*c;
      }
    }

    KYOSU_CALLABLE_OBJECT(sqr_t, sqr_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqr
//!   @brief Computes the square value.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr T sqr(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to for which square is computed.
//!
//!   **Return value**
//!
//!     Returns the square of its argument. i.e. `z*z` in an optimized way, if possible.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqr.cpp}
//======================================================================================================================
  inline constexpr auto sqr = eve::functor<sqr_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
