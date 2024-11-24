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
#include <kyosu/functions/sqr_abs.hpp>

namespace kyosu
{
  template<typename Options>
  struct maxmag_t : eve::strict_elementwise_callable<maxmag_t, Options>
  {
    template<typename Z0, typename Z1, typename ...Zs>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1> || (concepts::cayley_dickson<Zs> || ...))
      KYOSU_FORCEINLINE constexpr auto  operator()(Z0 const& z0, Z1 const& z1, Zs const & ...zs) const noexcept -> kyosu::as_cayley_dickson_t<Z0, Z1, Zs...>
    {
      if constexpr(sizeof...(Zs) == 0)
      {
        auto az0 = kyosu::sqr_abs(z0);
        auto az1 = kyosu::sqr_abs(z1);
        auto tmp = kyosu::if_else(eve::is_not_greater_equal(az0, az1), z1, z0);
        return kyosu::if_else(eve::is_not_greater_equal(az1, az0), z0, tmp);
      }
      else
      {
        using r_t = kyosu::as_cayley_dickson_t<Z0, Z1, Zs...>;
        r_t that((*this)(z0, z1));
        ((that = (*this)(that, zs)), ...);
        return that;
      }
    }

    template<concepts::real V0, concepts::real ...Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, Vs ... vs) const noexcept -> decltype(eve::maxmag(v0,vs...))
    { return eve::maxmag(v0,vs...); }

    KYOSU_CALLABLE_OBJECT(maxmag_t, maxmag_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var maxmag
//!   @brief Callable object computing the maxmag operation.
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
//!      template<typename ... Ts> auto maxmag(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the value which has the maximum of the absolute values between the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/maxmag.cpp}
//======================================================================================================================
  inline constexpr auto maxmag = eve::functor<maxmag_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
