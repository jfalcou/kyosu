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
#include <kyosu/functions/mul.hpp>

namespace kyosu
{
  template<typename Options>
  struct dot_t : kyosu::strict_tuple_callable<dot_t, Options>
  {
    template<typename... Ts>       struct result        : as_cayley_dickson<Ts...> {};
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...> {};

    template<concepts::cayley_dickson_like... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    KYOSU_FORCEINLINE typename result<Ts...>::type constexpr operator()(Ts...ts) const noexcept
    {
      return KYOSU_CALL(ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !concepts::cayley_dickson_like<Tup>)
      KYOSU_FORCEINLINE constexpr
    kumi::apply_traits_t<result,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
    { return KYOSU_CALL(t); }


    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> &&
             !concepts::cayley_dickson_like<Tup1> && !concepts::cayley_dickson_like<Tup2>)
      KYOSU_FORCEINLINE constexpr
    kumi::apply_traits_t<as_cayley_dickson_like, kumi::result::cat_t<Tup1, Tup2>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept
    { return EVE_DISPATCH_CALL(t1, t2); }

    KYOSU_CALLABLE_OBJECT(dot_t, dot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dot
//!   @brief `elementwise_callable` object computing the elementwise  dot product
//!     of the vector of the first half parameter by thevector of the last half.
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
//!      constexpr auto dot(auto z0,  auto z1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the dot product of `z0` and `z1`: `z0*conj(z1)`.
//!     Arguments can be a mix of floating or Cayley-Dickson values.
//!     for real typed inputs the result is real typed.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dot.cpp}
//======================================================================================================================
  inline constexpr auto dot = eve::functor<dot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace kyosu::_
{
  template<concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto dot_(KYOSU_DELAY(), O const & o, T0 z0, T1 z1) noexcept
  {
    return z0*conj(z1);
  }

  template<typename... Ts, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto dot_(KYOSU_DELAY(), O const & o, Ts... args) noexcept
  requires(sizeof...(Ts) > 3  && sizeof...(Ts)%2 == 0)
  {
    using r_t =  as_cayley_dickson_like_t<Ts...>;
    auto coeffs = eve::zip(r_t(args)...);
    auto [f,s]   = kumi::split(coeffs, kumi::index<sizeof...(Ts)/2>);
    auto tup = kumi::map([o](auto a, auto b) { return kyosu::mul[o](a, conj(b)); }, f, s);
    return add[o](tup);
  }

  template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto dot_(KYOSU_DELAY(), O const & o, Tup1 z0, Tup2 z1) noexcept
  requires(!concepts::cayley_dickson_like<Tup1> && !concepts::cayley_dickson_like<Tup2>)
  {
    auto tup = kumi::map([o](auto a, auto b) { return kyosu::mul[o](a, conj(b)); }, z0, z1);
    return add[o](tup);
  }
}
