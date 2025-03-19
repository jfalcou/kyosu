//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/mul.hpp>

namespace kyosu
{
  template<typename Options>
  struct ldiv_t : eve::strict_tuple_callable<ldiv_t, Options>
  {
    template<typename... Ts>       struct result       { using type = expected_result_t<eve::add,Ts...>; };
    template<concepts::real... Ts> struct result<Ts...>{ using type = eve::common_value_t<Ts...>; };

    template< concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1
            , concepts::cayley_dickson_like... Ts
            >
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE auto constexpr operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return KYOSU_CALL(t0,t1,ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<result,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return KYOSU_CALL(t); }

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
//!     constexpr auto ldiv(auto z0, auto zto zs...) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, `zs...`: Values to process.
//!
//!   **Return value**
//!
//!      - For two arguments Returns the left division  of the two arguments. This function not equivalent to z1/z0 as soon as multiplication
//!     is not commutative (i.e. for general Cayley-Dickson values with dimensionality strictly above 2).
//!      - For  more arguments the left division of the product of the arguments but the first, by the first is returned.
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
  template<eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto ldiv_(KYOSU_DELAY(), O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    return rec(v0)*(vs * ... );
  }

  template<eve::conditional_expr C, eve::callable_options O, typename T0, typename... Ts>
  EVE_FORCEINLINE constexpr auto ldiv_(KYOSU_DELAY(), C const& cond, O const&, T0 const& v0, Ts const&... vs) noexcept
  {
    auto that = ldiv(v0, vs...);
    return eve::detail::mask_op(cond, eve::detail::return_2nd, v0, that);
  }
}
