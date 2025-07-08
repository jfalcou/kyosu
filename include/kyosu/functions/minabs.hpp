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
  struct minabs_t : eve::tuple_callable<minabs_t, Options, eve::numeric_option, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like ...Zs>
    KYOSU_FORCEINLINE constexpr
    auto operator()(Z0 z0, Zs... zs) const noexcept -> decltype(eve::minabs(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE constexpr  kyosu::as_real_type_t<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

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
//!      //regular call
//!      template<typename ... Ts> auto minabs(Ts ... zs       ) const noexcept// 1
//!      template<typename Tup>    auto minabs(kumi::tuple Tup ) const noexcept// 2
//!
//!      // Semantic modifyiers
//!      auto minabs[raw](/* any previous overload*/)              noexcept;   // 3
//!      auto minabs[numeric](/* any previous overload*/auto  tup) noexcept;   // 4
//!      auto minabs[pedantic](/* any previous overload*/)         noexcept;   // 5
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `zi...`: Values to process.
//!     * `tup  `: tuple of values to process.
//!
//!   **Return value**
//!
//!     1. Returns elementwise  the square root minimum of the squared absolute values of the parameters.
//!     2 same as 1, but the parameters are from the tuple
//!     2. With the raw option no provision is made to enhance accuracy and avoid overflows
//!     3. Returns elementwise  the pedantic minimum of the  absolute values of the parameters.
//!     4. Returns elementwise  the numeric minimum of the  absolute values of the parameters.
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
    else if constexpr(O::contains(pedantic) || O::contains(numeric))
      return eve::min[o](kyosu::abs(z0), kyosu::abs(zs)...);
    else
      return eve::sqrt(eve::min[o](kyosu::sqr_abs(z0), kyosu::sqr_abs(zs)...));
  }
}
