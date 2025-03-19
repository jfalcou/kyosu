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
  struct mul_t : eve::strict_tuple_callable<mul_t, Options>
  {
    template<typename... Ts>       struct result       { using type = expected_result_t<eve::add,Ts...>; };
    template<concepts::real... Ts> struct result<Ts...>{ using type = eve::common_value_t<Ts...>; };

    template<typename T0, typename T1, typename... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE expected_result_t<eve::mul,T0,T1,Ts...> constexpr operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return KYOSU_CALL(t0,t1,ts...);
    }

    template<concepts::real T0, concepts::real T1, concepts::real... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
      EVE_FORCEINLINE eve::common_value_t<T0,T1,Ts...> constexpr operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return eve::mul(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<result,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return KYOSU_CALL(t); }

    KYOSU_CALLABLE_OBJECT(mul_t, mul_);
  };


//======================================================================================================================
//! @multogroup functions
//! @{
//!   @var mul
//!   @brief `tuple_callable` computing the product of its arguments.
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
//!      constexpr auto mul(auto ... xs)                                              noexcept; // 1
//!      constexpr auto mul(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto mul[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto mul[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
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
//!    1. The value of the product of the arguments is returned.
//!    2. The value of the product of the tuple elements is returned.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/mul.cpp}
//======================================================================================================================
  inline constexpr auto mul = eve::functor<mul_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto mul_(KYOSU_DELAY(), O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    return v0*(vs * ... );
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto mul_(KYOSU_DELAY(), C const& cond, O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    expected_result_t<eve::mul,T0,Ts...> that(v0);
    ((that = mul(that, vs)),...);
    return eve::detail::mask_op(cond, eve::detail::return_2nd, v0, that);
  }
}
