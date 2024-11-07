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
#include <kyosu/functions/to_complex.hpp>

namespace kyosu
{
  template<typename Options>
  struct lpnorm_t : eve::strict_elementwise_callable<lpnorm_t, Options>
  {
    template<typename P, typename Z1, typename ...Zs>
    requires(concepts::real<P>, concepts::cayley_dickson<Z1> || (concepts::cayley_dickson<Zs> || ...))
    KYOSU_FORCEINLINE constexpr auto  operator()(P p, Z1 const & z1, Zs const & ...zs) const noexcept -> decltype(eve::lpnorm(p, real(z1), real(zs)...))
    { return KYOSU_CALL(p,z1,zs...); }

    template<concepts::real P, concepts::real V1, concepts::real ...Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(P p, V1 v1, Vs... vs) const noexcept -> decltype(eve::lpnorm(p, real(v1), real(vs)...))
    { return eve::lpnorm(p,v1,vs...); }

    KYOSU_CALLABLE_OBJECT(lpnorm_t, lpnorm_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lpnorm
//!   @brief Callable object computing the lpnorm operation \f$ \left(\sum_{i = 0}^n
//! |x_i|^p\right)^{\frac1p} \f$.
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
//!      template< floating_ordered_value P, typename T, typename ... Ts> auto lpnorm(P p, T z,Ts ... zs ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `p`:   : positive floating ordered value
//!     * `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns \f$ \left(\sum_{i = 0}^n |x_i|^p\right)^{\frac1p} \f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lpnorm.cpp}
//======================================================================================================================
  inline constexpr auto lpnorm = eve::functor<lpnorm_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<typename P, typename Z1, typename ... Zs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto lpnorm_(KYOSU_DELAY(), O const&, P p, Z1 z1, Zs... zs) noexcept
  -> decltype(eve::lpnorm(p, real(z1), real(zs)...))
  {
    if constexpr(sizeof...(zs) == 0) return kyosu::abs(z1);
    else  return eve::lpnorm(p,  kyosu::abs(z1), kyosu::abs(zs)...);
  }
}
