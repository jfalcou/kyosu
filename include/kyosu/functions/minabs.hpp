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
#include <kyosu/functions/abs.hpp>

namespace kyosu
{
  template<typename Options>
  struct minabs_t : eve::strict_elementwise_callable<minabs_t, Options, eve::numeric_option, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Zs... zs) const noexcept -> decltype(eve::maxabs(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
    }

    KYOSU_CALLABLE_OBJECT(minabs_t, minabs_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var minabs
//!   @brief Callable object computing the minabs operation.
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
//!      template<typename ... Ts> auto minabs(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the minimum of the absolute values of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/minabs.cpp}
//======================================================================================================================
  inline constexpr auto minabs = eve::functor<minabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename ...Zs>
  KYOSU_FORCEINLINE constexpr
  auto minabs_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    if constexpr(concepts::real<Z0> && (... && concepts::real<Zs>))
      return eve::minabs[o](z0,zs...);
    else
     return eve::sqrt(eve::min[o](kyosu::sqr_abs(z0), kyosu::sqr_abs(zs)...));
  }
}
