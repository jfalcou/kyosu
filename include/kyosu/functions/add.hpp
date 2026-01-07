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
  struct add_t : eve::strict_tuple_callable<add_t, Options>
  {
    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...> {};

    template< concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1
            , concepts::cayley_dickson_like... Ts
            >
    requires(eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE typename result<T0,T1,Ts...>::type constexpr operator()(Ts...ts) const noexcept
    {
      return KYOSU_CALL(ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
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
//!
//!      // Lanes masking
//!      constexpr auto add[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto add[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
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
//!    1. The value of the sum of the arguments is returned.
//!    2. The value of the sum of the tuple elements is returned.
//!    3. [The operation is performed conditionnaly](@ref conditional)
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
  template<eve::callable_options O, typename... Ts>
  EVE_FORCEINLINE constexpr auto add_(KYOSU_DELAY(), O const&, Ts const&... vs) noexcept
  {
    return (vs + ... );
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto add_(KYOSU_DELAY(), C const& cond, O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    expected_result_t<eve::add,T0,Ts...> that(v0);
    ((that = add(that,vs)),...);
    return eve::detail::mask_op(cond, eve::detail::return_2nd, v0, that);
  }
}
