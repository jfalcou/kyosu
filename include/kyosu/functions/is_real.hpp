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
  struct is_real_t : eve::elementwise_callable<is_real_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z c) const noexcept
    {
      if constexpr(kyosu::concepts::real<Z>)
      {
        return eve::true_(eve::as(c));
      }
      else if constexpr(kyosu::concepts::complex<Z>)
      {
        return eve::is_eqz(ipart(c));
      }
      else
      {
        get<0>(c) = eve::zero(eve::as(get<0>(c)));
        return kumi::all_of(c, [](auto const& e) { return eve::is_eqz(e); });
      }
    }

    KYOSU_CALLABLE_OBJECT(is_real_t, is_real_);
  };


//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_real
//!   @brief test if the parameter is real.
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
//!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto is_real(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true if its  [pure](@ref kyosu::pure) part is zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_real.cpp}
//======================================================================================================================
  inline constexpr auto is_real = eve::functor<is_real_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
