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
#include <kyosu/functions/sqr_abs.hpp>

namespace kyosu
{
  template<typename Options>
  struct minmag_t : eve::strict_elementwise_callable<minmag_t, Options>
  {
    template<concepts::cayley_dickson_like Z0>
    KYOSU_FORCEINLINE constexpr
    Z0 operator()(Z0 z0) const noexcept
    {
      return z0;
    }

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    typename kyosu::as_cayley_dickson_like_t<Z0,Z1,Zs...> operator()(Z0 z0, Z1 z1, Zs... zs) const noexcept
    {
      return KYOSU_CALL(z0, z1, zs...);
    }

    KYOSU_CALLABLE_OBJECT(minmag_t, minmag_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var minmag
//!   @brief Callable object computing the minmag operation.
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
//!      template<typename ... Ts> auto minmag(Ts ... zi ) const noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns elementwise  the value which has the minimum of the absolute values between the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/minmag.cpp}
//======================================================================================================================
  inline constexpr auto minmag = eve::functor<minmag_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename Z1, typename ...Zs>
  KYOSU_FORCEINLINE constexpr
  auto minmag_(KYOSU_DELAY(), O const& o, Z0 z0, Z1 z1, Zs... zs) noexcept
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1> && (... && concepts::real<Zs>))
      return eve::minmag(z0, z1, zs...);
    else  if constexpr(sizeof...(Zs) == 0)
    {
      auto az0 = kyosu::sqr_abs(z0);
      auto az1 = kyosu::sqr_abs(z1);
      auto tmp = kyosu::if_else(eve::is_not_greater_equal(az1, az0), z1, z0);
      return kyosu::if_else(eve::is_not_greater_equal(az0, az1), z0, tmp);
    }
    else
    {
      using r_t = kyosu::as_cayley_dickson_t<Z0, Z1, Zs...>;
      r_t that(minmag(z0, z1));
      ((that = minmag(that, zs)), ...);
      return that;
    }
  }
}
