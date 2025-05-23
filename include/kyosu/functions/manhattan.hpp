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
  struct manhattan_t : eve::strict_tuple_callable<manhattan_t, Options, eve::pedantic_option>
  {

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Zs... zs) const noexcept -> decltype(eve::manhattan(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
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
//!     The value of the sum of the  values (the\f$l_1\f$ norm) of the \f$l_1\f$ norm of its arguments is returned.
//!
//!  @note This is NOT `lpnorm(1, x0, xs...)` which is the \f$l_1\f$ norm of \f$l_2\f$ norm of its arguments.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: L1 norm](https://mathworld.wolfram.com/L1-Norm.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/manhattan.cpp}
//======================================================================================================================
  inline constexpr auto manhattan = eve::functor<manhattan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename ...Zs>
  KYOSU_FORCEINLINE constexpr
  auto manhattan_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    if constexpr(concepts::real<Z0> && (... && concepts::real<Zs>))
      return  eve::manhattan[o](z0, zs...);
    else
      return eve::manhattan[o](kumi::flatten(kumi::make_tuple(z0, zs...)));
  }
}
