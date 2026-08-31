//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/abi.hpp>
#include <kyosu/types/concepts.hpp>
#include <kyosu/types/traits.hpp>
#include <eve/traits/overload.hpp>

namespace kyosu::_
{
  EVE_CALLABLE_NAMESPACE();
}

//  EVE-related macro that use kyosu::_ as the deferred namespace
#define KYOSU_CALLABLE_OBJECT(TYPE, NAME) EVE_CALLABLE_OBJECT_FROM(kyosu::_, TYPE, NAME)
#define KYOSU_CALL(...) EVE_DISPATCH_CALL(__VA_ARGS__)
#define KYOSU_DELAY() EVE_REQUIRES(eve::cpu_)

namespace kyosu
{
  namespace _
  {
    //==================================================================================================================
    // Sits between a kyosu callable and the eve base it would otherwise derive from, and overrides behavior(), the
    // entry point eve dispatches every call through.
    //
    // eve computes f[cond](x) as if_else(cond, f(x), x): the lanes cond rejects carry x itself, so x and f(x) have to
    // share a type. They do not when f answers a complex to a real argument - kyosu::sqrt(-1.0) is a complex where x
    // is a double - and eve cannot turn a wide<double> into a wide<complex<double>> on its own.
    //
    // Promoting x to complexify_t<T> before Base::behavior() runs makes both sides complex, and eve hands the
    // promoted x back untouched.
    //
    // The promotion is unconditional, and that is deliberate: deciding it from the type Base::behavior() answers
    // would mean instantiating it inside this one, which eve also calls under is_invocable when it aggregates a
    // wide - turning "not invocable" into a hard error. A callable that answers a real must therefore keep its eve
    // base rather than this one.
    //==================================================================================================================
    template<typename Base> struct promoting_callable : Base
    {
      template<eve::callable_options O, typename T, typename... Ts>
      KYOSU_FORCEINLINE constexpr auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
      {
        constexpr bool masked =
          O::contains(eve::condition_key) && !eve::match_option<eve::condition_key, O, eve::ignore_none_>;

        if constexpr (masked && concepts::real<T>) return Base::behavior(arch, opts, complexify_t<T>(x0), xs...);
        else return Base::behavior(arch, opts, x0, xs...);
      }
    };
  }

  //====================================================================================================================
  //! @addtogroup traits
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //! @struct promoting_elementwise_callable
  //! @brief CRTP base for a kyosu callable that answers a complex to a real argument.
  //!
  //! Behaves as eve::elementwise_callable, which it derives from, and promotes a real argument to its complex
  //! counterpart when the call carries a condition. A masked call answers its own argument on the lanes the condition
  //! rejects, so the two have to share a type.
  //!
  //! Use it for a callable whose return type is complexify_t or complexify_if_t. One that answers a real - abs, arg -
  //! keeps eve::elementwise_callable: promoting its argument would create the very mismatch this removes. One that
  //! cannot honour a condition at all uses eve::callable, which refuses `operator[]`.
  //!
  //! @tparam Func          The callable being defined
  //! @tparam OptionsValues Type of the stored options
  //! @tparam Options       List of supported option specifications
  //====================================================================================================================
  template<template<typename> class Func, typename OptionsValues, typename... Options>
  struct promoting_elementwise_callable
    : _::promoting_callable<eve::elementwise_callable<Func, OptionsValues, Options...>>
  {
  };

  //====================================================================================================================
  //! @struct promoting_strict_elementwise_callable
  //! @brief The eve::strict_elementwise_callable counterpart of kyosu::promoting_elementwise_callable.
  //!
  //! Same promotion of a masked real argument, without the common-type conversion eve applies to arguments of
  //! differing types.
  //!
  //! @tparam Func          The callable being defined
  //! @tparam OptionsValues Type of the stored options
  //! @tparam Options       List of supported option specifications
  //====================================================================================================================
  template<template<typename> class Func, typename OptionsValues, typename... Options>
  struct promoting_strict_elementwise_callable
    : _::promoting_callable<eve::strict_elementwise_callable<Func, OptionsValues, Options...>>
  {
  };

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
