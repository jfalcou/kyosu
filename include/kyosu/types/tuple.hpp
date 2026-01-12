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
  //====================================================================================================================
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct strict_tuple_callable : eve::strict_elementwise_callable<Func, OptionsValues, Options...>
  {
    using base_t = eve::strict_elementwise_callable<Func, OptionsValues, Options...>;

    template<eve::callable_options O, kumi::product_type T>
    requires(!concepts::cayley_dickson_like<T>)
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x) const
    {
      return kumi::apply( [&](auto... a) { return static_cast<base_t const&>(*this).behavior(arch, opts, a...); }, x);
    }

    template<eve::callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      return base_t::behavior(arch, opts, x0, xs...);
    }
  };
}
