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
  struct maxmag_t : eve::tuple_callable<maxmag_t, Options>
  {

    template<concepts::cayley_dickson_like Z0>
    KYOSU_FORCEINLINE constexpr
    Z0 operator()(Z0 z0) const noexcept
    {
      return z0;
    }

    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like Z1, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    typename  kyosu::as_cayley_dickson_like_t<Z0,Z1,Zs...> operator()(Z0 z0, Z1 z1, Zs... zs) const noexcept
    {
      return KYOSU_CALL(z0, z1, zs...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE constexpr  kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

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
//!      //regular call
//!      template<typename ... Ts> auto minabs(Ts ... zs       ) const noexcept// 1
//!      template<typename Tup>    auto minabs(kumi::tuple Tup ) const noexcept// 2
//!
//!      // Semantic modifyiers
//!      auto minabs[raw](/* any previous overload*/)      noexcept;           // 3
//!      auto minabs[numeric](/* any previous overload*/)  noexcept;           // 4
//!      auto minabs[pedantic](/* any previous overload*/) noexcept;           // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: cayley_dickson_like to process.
//!     * `tup  `: tuple of cayley_dickson_like values to process.
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

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename Z1, typename ...Zs>
  KYOSU_FORCEINLINE constexpr
  auto maxmag_(KYOSU_DELAY(), O const& o, Z0 z0, Z1 z1, Zs... zs) noexcept
  {
    if constexpr(concepts::real<Z0> && concepts::real<Z1> && (... && concepts::real<Zs>))
      return eve::maxmag(z0, z1, zs...);
    else if constexpr(sizeof...(Zs) == 0)
    {
      auto az0 = kyosu::sqr_abs(z0);
      auto az1 = kyosu::sqr_abs(z1);
      auto tmp = kyosu::if_else(eve::is_not_greater_equal(az0, az1), z1, z0);
      return kyosu::if_else(eve::is_not_greater_equal(az1, az0), z0, tmp);
    }
    else
    {
      using r_t = kyosu::as_cayley_dickson_t<Z0, Z1, Zs...>;
      r_t that(kyosu::maxmag(z0, z1));
      ((that = kyosu::maxmag(that, zs)), ...);
      return that;
    }
  }
}
