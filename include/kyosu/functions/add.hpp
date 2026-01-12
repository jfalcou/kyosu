//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/types/tuple.hpp>

namespace kyosu
{
  template<typename Options>
  struct add_t : kyosu::strict_tuple_callable<add_t, Options, eve::kahan_option>
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

    KYOSU_CALLABLE_OBJECT(add_t, add_);
  };


//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var add
//!   @brief `tuple_callable` computing the sum of its arguments.
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
//!      constexpr auto add(auto ... xs)                                              noexcept; // 1
//!      constexpr auto add(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!      constexpr auto add[kahan] (/*any of the above overloads*/)                   noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto add[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 4
//!      constexpr auto add[logical_value auto m](/*any of the above overloads*/)     noexcept; // 4
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs...`:  real or cayley-dickson arguments.
//!     * `tup`: kumi tuple of arguments.
//!
//!   **Return value**
//!
//!     1. The value of the sum of the arguments is returned.
//!     2. The value of the sum of the tuple elements is returned.
//!     3. kahan algorithm is used to enhance accuracy.
//!     4. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/add.cpp}
//======================================================================================================================
  inline constexpr auto add = eve::functor<add_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, concepts::cayley_dickson_like T0, concepts::cayley_dickson_like... Ts>
  EVE_FORCEINLINE constexpr auto add_(KYOSU_DELAY(), O const& o, T0 const& t0, Ts const&... ts) noexcept
  {
    using r_t = as_cayley_dickson_t<T0, Ts...>;
    if constexpr(concepts::real<r_t>)
      return eve::add[o](t0, ts...);
    else if constexpr(sizeof...(Ts) == 0)
      return t0;
    else
      return kumi::map(eve::add[o], r_t(t0), r_t(ts)...);
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto add_(KYOSU_DELAY(), C const& cond, O const& o, T0 const& v0, Ts const&... vs) noexcept
  {
    using r_t = as_cayley_dickson_t<T0, Ts...>;
    return eve::detail::mask_op(cond, eve::detail::return_2nd, r_t(v0), add(v0, vs...));
  }
}
