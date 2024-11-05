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

namespace kyosu
{
  template<typename Options>
  struct manhattan_t : eve::tuple_callable<manhattan_t, Options>
  {
    template<eve::value Z0, eve::value ...Zs>
    requires( concepts::cayley_dickson<Z0> || (concepts::cayley_dickson<Zs> || ...) )
      KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Zs... zs) const noexcept -> decltype(eve::manhattan(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
    }

    template<concepts::real T0, concepts::real... Ts>
    auto operator()(T0 t0, Ts... ts) const noexcept -> decltype( eve::manhattan(t0, ts...))
    {
      return eve::manhattan(t0, ts...);
    }

    KYOSU_CALLABLE_OBJECT(manhattan_t, manhattan_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var manhattan
//!   @brief Computes the sum of the absolute values of all terms of all the parameters.
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
//!     constexpr auto manhattan(auto z0, auto ...zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `...zs`: Value to process.
//!
//!   **Return value**
//!
//!     The value of the sum of the  values of the \f$\l_1\f$ norm of its arguments is returned.
//!
//!  @note : This is NOT `lpnorm(1, x0, xs...)` which is \f$\l_1\f$ norm of \f$\l_2\f$ norm of its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/manhattan.cpp}
//======================================================================================================================
  inline constexpr auto manhattan = eve::functor<manhattan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z0,  typename ...Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto manhattan_(KYOSU_DELAY(), O const&, Z0 const& z0, Zs const& ...zs) noexcept
  {
    if constexpr(concepts::cayley_dickson<Z0> || (concepts::cayley_dickson<Zs> || ...) )
      return eve::manhattan(kumi::flatten(kumi::cat(z0, zs...)));
    else
      return eve::manhattan(z0, zs...);
  }
}
