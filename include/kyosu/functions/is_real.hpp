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

namespace kyosu
{
  template<typename Options>
  struct is_real_t : eve::elementwise_callable<is_real_t, Options>
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept { return KYOSU_CALL(z); }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr eve::as_logical_t<V> operator()(V v) const noexcept { return eve::true_(eve::as(v)); }

    KYOSU_CALLABLE_OBJECT(is_real_t, is_real_);
  };


//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_real
//!   @brief test if the parameter is real.
//!
//!   **Defined in Header**
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
//!      template<kyosu::concepts::cayley_dickson T> constexpr auto is_real(T z) noexcept;
//!      template<eve::floating_ordered_value T>     constexpr auto is_real(T z) noexcept;
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

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto is_real_(KYOSU_DELAY(), O const&, Z c) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      return eve::is_eqz(ipart(c));
    }
    else
    {
      get<0>(c) = eve::zero(eve::as(get<0>(c)));
      return kumi::all_of(c, [](auto const& e) { return eve::is_eqz(e); });
    }
  }
}
