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
  struct maxabs_t : eve::tuple_callable<maxabs_t, Options, flat_option, eve::numeric_option, eve::pedantic_option>
  {
    template<concepts::cayley_dickson_like Z0, concepts::cayley_dickson_like... Zs>
    KYOSU_FORCEINLINE constexpr auto operator()(Z0 z0, Zs... zs) const noexcept
      -> decltype(eve::maxabs(real(z0), real(zs)...))
    {
      return KYOSU_CALL(z0, zs...);
    }

    template<eve::concepts::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr kyosu::as_real_type_t<kumi::apply_traits_t<eve::common_value, Tup>> operator()(
      Tup t) const noexcept
    requires(kumi::size_v<Tup> >= 2)
    {
      return EVE_DISPATCH_CALL(t);
    }

    KYOSU_CALLABLE_OBJECT(maxabs_t, maxabs_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var maxabs
  //!   @brief Callable object computing the maxabs operation.
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
  //!      template<typename ... Ts> auto maxabs(Ts ... zs       ) const noexcept// 1
  //!      template<typename Tup>    auto maxabs(kumi::tuple Tup ) const noexcept// 2
  //!
  //!      // Semantic modifyiers
  //!      auto maxabs[raw](/* any previous overload*/) const      noexcept;     // 3
  //!      auto maxabs[numeric](/* any previous overload*/) const  noexcept;     // 4
  //!      auto maxabs[pedantic](/* any previous overload*/) const noexcept;     // 5
  //!      auto maxnabs[flat](/* any previous overload*/) const    noexcept;     // 6
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `zi...`: cayley_dickson_like values to process.
  //!     * `tup  `: tuple of cayley_dickson_like values to process.
  //!
  //!   **Return value**
  //!
  //!     1. Returns elementwise  the square root maximum of the squared absolute values of the parameters.
  //!     2  Same as 1, but the parameters are from the tuple
  //!     3. With the raw option no provision is made to enhance accuracy and avoid overflows
  //!     4. With the `flat` option it is the \f$\l_\infty\f$ norm of all the components that is computed.
  //!     5. Returns elementwise  the pedantic maximum of the  absolute values of the parameters.
  //!     6. Returns elementwise  the numeric maximum of the  absolute values of the parameters.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/maxabs.cpp}
  //======================================================================================================================
  inline constexpr auto maxabs = eve::functor<maxabs_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename Z0, typename... Zs>
  KYOSU_FORCEINLINE constexpr auto maxabs_(KYOSU_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    if constexpr (concepts::real<Z0> && (... && concepts::real<Zs>)) return eve::maxabs[o](z0, zs...);
    else if constexpr (O::contains(flat)) return eve::maxabs[o](kumi::flatten(kumi::tuple{z0, zs...}));
    else if constexpr (O::contains(pedantic) || O::contains(numeric))
      return eve::max[o](kyosu::abs(z0), kyosu::abs(zs)...);
    else return eve::sqrt(eve::max[o](kyosu::sqr_abs(z0), kyosu::sqr_abs(zs)...));
  }
}
