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
#include <kyosu/functions/nthroot.hpp>

namespace kyosu
{
  template<typename Options>
  struct geommean_t : kyosu::strict_tuple_callable<geommean_t, Options, eve::pedantic_option, eve::kahan_option>
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

    KYOSU_CALLABLE_OBJECT(geommean_t, geommean_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var geommean
//!   @brief Computes a geometric mean of the parameters.
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
//!      constexpr auto geommean(auto ... xs)                                              noexcept; // 1
//!      constexpr auto geommean(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!      conséexpr auto geommean[pedantic](/*any of the above overloads*/)                 noexcept; // 3
//!      constexpr auto geommean[kahan] (/*any of the above overloads*/)                   noexcept; // 4
//!
//!      // Lanes masking
//!      constexpr auto geommean[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 5
//!      constexpr auto geommean[logical_value auto m](/*any of the above overloads*/)     noexcept; // 5
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
//!     1. The value of the geomeric mean of the arguments is returned.
//!     2. The value of the geomeric mean of the tuple elements is returned.
//!     3. avoid spurious overflows.
//!     4. kahan algorithm is used to enhance accuracy.
//!     5. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/geommean.cpp}
//======================================================================================================================
  inline constexpr auto geommean = eve::functor<geommean_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{

  template<concepts::cayley_dickson_like T0, concepts::cayley_dickson_like ...Ts, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto geommean_(KYOSU_DELAY(), O const& o, T0 const & t0, Ts const &...  ts) noexcept
  {
    using r_t = as_cayley_dickson_t<T0, Ts...>;
    using f_t = eve::element_type_t<r_t>;
    if constexpr(concepts::real<r_t>)
      return eve::geommean(t0, ts...);
    else
    {
      constexpr auto p = sizeof...(Ts)+1;
      if constexpr(p == 1)
        return t0;
      else
        return kyosu::nthroot(kyosu::mul[o](t0, ts...), p);
    }
  }
}
