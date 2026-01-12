//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/convert.hpp>
#include <kyosu/functions/add.hpp>

namespace kyosu
{
  template<typename Options>
  struct sub_t : kyosu::strict_tuple_callable<sub_t, Options, eve::kahan_option>
  {
    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...> {};

    template<concepts::cayley_dickson_like... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE typename result<Ts...>::type constexpr operator()(Ts...ts) const noexcept
    {
      return KYOSU_CALL(ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !concepts::cayley_dickson_like<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<result,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 1) { return KYOSU_CALL(t); }

    KYOSU_CALLABLE_OBJECT(sub_t, sub_);
  };


//======================================================================================================================
//! @subtogroup functions
//! @{
//!   @var sub
//!   @brief `tuple_callable` computing the difference of its first argument with the sum of the others.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto sub(auto ... xs)                                              noexcept; // 1
//!      constexpr auto sub(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!      constexpr auto add[kahan] (/*any of the above overloads*/)                   noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto sub[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 4
//!      constexpr auto sub[logical_value auto m](/*any of the above overloads*/)     noexcept; // 4
//!
//!   }
//!   @endcode
//!
//!!   **Parameters**
//!
//!     * `xs` :  real or cayley-dickson arguments.
//!     * `tup` : kumi tuple of arguments.
//!
//!   **Return value**
//!
//!    1. The value of the difference of its first argument with the sum of the others.
//!    2. same on 1. the tuple elements.
//!    3. kahan algorithm is used to enhance accuracy.
//!    4. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/sub.cpp}
//======================================================================================================================
  inline constexpr auto sub = eve::functor<sub_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{

  template<eve::callable_options O, concepts::cayley_dickson_like T0, concepts::cayley_dickson_like... Ts>
  EVE_FORCEINLINE constexpr auto sub_(KYOSU_DELAY(), O const& o, T0 const& t0, Ts const&... ts) noexcept
  {
    using r_t = as_cayley_dickson_t<T0, Ts...>;
    if constexpr(concepts::real<r_t>)
      return eve::sub[o](t0, ts...);
    else if constexpr(sizeof...(Ts) == 0)
      return t0;
    else
      return kumi::map(eve::sub[o], r_t(t0), r_t(ts)...);
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto sub_(KYOSU_DELAY(), C const& cond, O const& o, T0 const& v0, Ts const&... vs) noexcept
  {
    using r_t = as_cayley_dickson_t<T0, Ts...>;
    return eve::detail::mask_op(cond, eve::detail::return_2nd, r_t(v0), kyosu::sub[o](v0, vs...));
  }
}
