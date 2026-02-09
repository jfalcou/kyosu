//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/mul.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/sqr_abs.hpp>

namespace kyosu
{
  template<typename Options> struct ldiv_t : kyosu::strict_tuple_callable<ldiv_t, Options, eve::kahan_option>
  {
    template<typename... Ts> struct result : as_cayley_dickson<Ts...>
    {
    };
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...>
    {
    };

    template<concepts::cayley_dickson_like... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE typename result<Ts...>::type constexpr operator()(Ts... ts) const noexcept
    {
      return KYOSU_CALL(ts...);
    }

    template<eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !concepts::cayley_dickson_like<Tup>)
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<result, Tup> operator()(Tup const& t) const noexcept
    requires(kumi::size_v<Tup> >= 1)
    {
      return KYOSU_CALL(t);
    }

    KYOSU_CALLABLE_OBJECT(ldiv_t, ldiv_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var ldiv
  //!   @brief Computes the left division of the product of the arguments but the first
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
  //!     // Regular overloads
  //!     constexpr auto ldiv(auto xs...) noexcept;                                     noexcept; // 1
  //!     constexpr auto dliv(eve::non_empty_product_type auto const& tup)             noexcept; // 2
  //!     constexpr auto ldiv[kahan](/*any of the above overloads*/)                    noexcept; // 3
  //!
  //!     // Lanes masking
  //!     constexpr auto ldiv[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 4
  //!     constexpr auto ldiv[logical_value auto m](/*any of the above overloads*/)     noexcept; // 4
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `xs...`: Values to process.
  //!     * `tup` : kumi tuple of arguments.
  //!
  //!   **Return value**
  //!
  //!      1. left division.
  //!         * For one argument returns the inverse of the argument
  //!         * For two arguments returns the left division  of the two arguments. This function is not equivalent to z1/z0 as
  //!           soon as multiplication is not commutative (i.e. for general Cayley-Dickson values with dimensionality strictly above 2).
  //!         * For  more arguments the left division of the product of the arguments but the first, by the first is returned.
  //!      2. same as 1. on the tuple elements.
  //!      3. kahan algorithm is used to enhance accuracy.
  //!      4. [The operation is performed conditionnaly](@ref conditional)
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/ldiv.cpp}
  //======================================================================================================================
  inline constexpr auto ldiv = eve::functor<ldiv_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, concepts::cayley_dickson_like... Ts>
  EVE_FORCEINLINE constexpr auto ldiv_(KYOSU_DELAY(), O const& o, Ts const&... ts) noexcept
  {
    if constexpr (sizeof...(Ts) == 1) return kyosu::rec(ts...);
    else
    {
      using r_t = as_cayley_dickson_t<Ts...>;
      auto tup = kumi::make_tuple(ts...);
      auto [f, s] = kumi::split(tup, kumi::index<1>);
      if constexpr (concepts::complex_like<r_t>) return kyosu::div(kumi::cat(s, f));
      else return kyosu::mul[o](kyosu::conj(kumi::get<0>(f)), kyosu::mul[o](s)) / sqr_abs(kumi::get<0>(f));
    }
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto ldiv_(KYOSU_DELAY(), C const& cond, O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    auto that = ldiv(v0, vs...);
    return eve::detail::mask_op(cond, eve::detail::return_2nd, v0, that);
  }
}
