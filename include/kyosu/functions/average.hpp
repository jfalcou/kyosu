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
  struct average_t : kyosu::strict_tuple_callable<average_t, Options, eve::pedantic_option, eve::kahan_option>
  {
    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...> {};

    template<concepts::cayley_dickson_like... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    KYOSU_FORCEINLINE constexpr typename result<Ts...>::type operator()(Ts ...ts) const noexcept
    { return KYOSU_CALL(ts...); }


    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !concepts::cayley_dickson_like<Tup>)
    EVE_FORCEINLINE constexpr  kumi::apply_traits_t<result,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 1)
    { return KYOSU_CALL(t); }

    KYOSU_CALLABLE_OBJECT(average_t, average_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var average
//!   @brief Computes the average of the parameters.
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
//!      // Regular overloads
//!      constexpr auto average(auto ... xs)                                              noexcept; // 1
//!      constexpr auto average(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!      conséexpr auto average[pedantic](/*any of the above overloads*/)                 noexcept; // 3
//!      constexpr auto average[kahan] (/*any of the above overloads*/)                   noexcept; // 4
//!
//!      // Lanes masking
//!      constexpr auto average[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 5
//!      constexpr auto average[logical_value auto m](/*any of the above overloads*/)     noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs...`: Values to process. Can be a mix of cayley_dickson_like values.
//!     * `tup : kumi tuple of arguments.
//!
//!   **Return value**
//!
//!     1. The value of the arithmetic mean of the arguments is returned.
//!     2. The value of the arithmetic mean of the tuple elements is returned.
//!     3. avoid spurious overflows.
//!     4. kahan algorithm is used to enhance accuracy.
//!     5. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/average.cpp}
//======================================================================================================================
  inline constexpr auto average = eve::functor<average_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{

  template<concepts::cayley_dickson_like T0, concepts::cayley_dickson_like ...Ts, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto average_(KYOSU_DELAY(), O const& o, T0 const & t0, Ts const &...  ts) noexcept
  {
    using r_t = as_cayley_dickson_t<T0, Ts...>;
    if constexpr(concepts::real<r_t>)
      return eve::average[o](t0, ts...);
    else if constexpr(sizeof...(Ts) == 0)
      return t0;
    else if constexpr(O::contains(eve::pedantic))
    {
      using f_t =  eve::element_type_t<r_t>;
      auto invs = eve::rec(f_t(sizeof...(Ts))+1);
      return average[o.drop(eve::pedantic)](t0*invs, (ts*invs)...);
    }
    else
    {
      return add[o](t0, ts...)/(sizeof...(Ts)+1);
    }
  }
}
