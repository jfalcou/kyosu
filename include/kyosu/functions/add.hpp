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
  struct add_t : eve::strict_elementwise_callable<add_t, Options>
  {
    template < typename Z0,  typename Z1>
    requires(concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>)
    KYOSU_FORCEINLINE auto constexpr operator()(Z0 t0,  Z1 t1) const noexcept -> decltype(t0+t1)
    {
      return t0+t1;
    }

    template<typename Z0, typename Z1, typename ...Zs>
    requires((concepts::cayley_dickson<Z0> || concepts::cayley_dickson<Z1>
              || ( concepts::cayley_dickson<Zs> || ...)) && (sizeof...(Zs) > 0)
            )
    KYOSU_FORCEINLINE constexpr auto  operator()(Z0 z0, Z1 z1, Zs ...zs) const noexcept  -> decltype(z0+(z1+...+ zs))
    { return KYOSU_CALL(z0,z1,zs...); }

    template<concepts::real V0, concepts::real V1, concepts::real ...Vs>
    KYOSU_FORCEINLINE constexpr auto operator()(V0 v0, V1 v1, Vs...vs) const noexcept -> decltype(v0+(v1+...+ vs))
    { return eve::add[this->options()](v0,v1,vs...); }

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
  template<typename  C0, typename  C1,  typename ...Cs, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto add_(KYOSU_DELAY(), O const& o,
                                            C0 const & c0, C1 const &  c1, Cs const &...  cs) noexcept
  -> decltype(C0()+(C1()+ ... +Cs()))
    requires(sizeof...(Cs) > 0)
  {
    using r_t = decltype(C0()+(C1()+ ... +Cs()));
    using er_t = eve::element_type_t<r_t>;
    r_t r0   = kyosu::convert(c0, eve::as<er_t>())+  kyosu::convert(c1, eve::as<er_t>());
    ((r0 = kyosu::add[o](r0, kyosu::convert(cs, eve::as<er_t>()))), ...);
    return r0;
  }
}
