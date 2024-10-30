//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>
#include <eve/module/math.hpp>

namespace kyosu::detail
{
  template<typename Func> struct constant_t;

  template<template<typename> typename Func, typename Opts>
  struct constant_t<Func<Opts>> : Func<Opts>
  {
    using base_callable = Func<Opts>;

    template<typename T>
    EVE_FORCEINLINE constexpr auto operator[](T t)
    const requires( requires(base_callable const& b) { b[t];} )
    {
      auto new_traits = base_callable::base::operator[](t);
      return  constant_t<Func<decltype(new_traits)>>{new_traits};
    }

    using base_callable::operator();

    template<concepts::cayley_dickson T>
    requires( requires(base_callable const& b){ b(as<as_real_type_t<T>>{}); } )
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const
    {
      return T{base_callable::operator()(as<as_real_type_t<T>>{})};
    }

    KYOSU_CALLABLE_OBJECT(constant_t, constant_);
  };

  template<auto Constant>
  inline constexpr constant_t<eve::tag_t<Constant>> as_constant = {};
}

//======================================================================================================================
// List of all EVE constants we re-propagate
//======================================================================================================================
namespace kyosu
{
  // Direct reuse
  using eve::zero;
  using eve::true_;
  using eve::false_;

  // Wrapping required
  inline constexpr auto half = detail::as_constant<eve::half>;
  inline constexpr auto pi   = detail::as_constant<eve::pi>;
}
