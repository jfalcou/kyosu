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
  struct mul_t : eve::strict_tuple_callable<mul_t, Options,  eve::kahan_option>
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
  template<eve::callable_options O, typename T0>
  EVE_FORCEINLINE constexpr auto mul_(KYOSU_DELAY(), O const&, T0 v0) noexcept
  {
    return v0;
  }

  template<eve::callable_options O, typename T0, typename T1, typename... Ts>
  EVE_FORCEINLINE constexpr auto mul_(KYOSU_DELAY(), O const& o, T0 const& v0, T1 const& v1, Ts const&... vs) noexcept
  {
    if constexpr((sizeof...(Ts) == 0 ))
    {
      if constexpr( concepts::complex<T0> && concepts::complex<T1> && O::contains(eve::kahan))
      {
        auto [aa, bb] = v0;
        auto [cc, dd] = v1;
        auto k =  [](auto a,  auto b,  auto c,  auto d){
          auto w = c*d;
          auto e = eve::fms(c, d, w);
          auto f = eve::fma(a, b, w);
          return f+e;
        };
        auto r = k(aa, cc, -bb, dd);
        auto i = k(aa, dd,  bb, cc);
        return  as_cayley_dickson<T0, T1>(r, i);
      }
      else
      {
        return v0*v1;
      };
    }
    else
    {
      auto that(mul[o](v0, v1));
      ((that = mul[o](that, vs)),...);
      return that;
    }
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto mul_(KYOSU_DELAY(), C const& cond, O const& o, T0 const& v0, Ts const&... vs) noexcept
  {
    expected_result_t<eve::mul,T0,Ts...> that(v0);
    ((that = mul(that, vs)),...);
    return eve::detail::mask_op(cond, eve::detail::return_2nd, v0, that);
  }
}
