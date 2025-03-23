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

namespace kyosu
{
  template<typename Options>
  struct div_t : eve::strict_tuple_callable<div_t, Options>
  {
    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...> {};

    template< concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1
            , concepts::cayley_dickson_like... Ts
            >
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE typename result<T0,T1,Ts...>::type constexpr operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return KYOSU_CALL(t0,t1,ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<result,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return KYOSU_CALL(t); }

    KYOSU_CALLABLE_OBJECT(div_t, div_);
  };


//======================================================================================================================
//! @divtogroup functions
//! @{
//!   @var div
//!   @brief `tuple_callable` computing the division of its first argument with the product of the others.
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
//!      constexpr auto div(auto ... xs)                                              noexcept; // 1
//!      constexpr auto div(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto div[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto div[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
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
//!    1. The value of the division of its first argument with the product of the others.
//!    2. same on 1. the tuple elements.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/div.cpp}
//======================================================================================================================
  inline constexpr auto div = eve::functor<div_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto div_(KYOSU_DELAY(), O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    return v0/(vs * ... );
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto div_(KYOSU_DELAY(), C const& cond, O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    expected_result_t<eve::div,T0,Ts...> that(v0);
    ((that = div(that,vs)),...);
    return eve::detail::mask_op(cond, eve::detail::return_2nd, v0, that);
  }
}
