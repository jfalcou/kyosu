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
  template<typename Options> struct kronecker_t : eve::strict_tuple_callable<kronecker_t, Options>
  {
    template<typename... Ts> struct result : as_real_type<as_cayley_dickson_t<Ts...>>
    {
    };
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...>
    {
    };

    template<concepts::cayley_dickson_like T0, concepts::cayley_dickson_like T1, concepts::cayley_dickson_like... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE typename result<T0, T1, Ts...>::type constexpr operator()(T0 t0, T1 t1, Ts... ts) const noexcept
    {
      return KYOSU_CALL(t0, t1, ts...);
    }

    template<eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<result, Tup> operator()(Tup const& t) const noexcept
    requires(kumi::size_v<Tup> >= 2)
    {
      return KYOSU_CALL(t);
    }

    KYOSU_CALLABLE_OBJECT(kronecker_t, kronecker_);
  };

  //======================================================================================================================
  //! @kroneckertogroup functions
  //! @{
  //!   @var kronecker
  //!   @brief `tuple_callable` computing the \f$\delta\f$ (Kronecker symbol) of its arguments.
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
  //!      constexpr auto kronecker(auto ... xs)                                              noexcept; // 1
  //!      constexpr auto kronecker(eve::non_empty_product_type auto const& tup)             noexcept; // 2
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
  //!    1. The value of the kronecker symbol of the arguments as a real value.
  //!    2. Same but the arguments are in the tuple.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/kronecker.cpp}
  //======================================================================================================================
  inline constexpr auto kronecker = eve::functor<kronecker_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<eve::callable_options O, typename T0, typename T1, typename... Ts>
  EVE_FORCEINLINE constexpr auto kronecker_(
    KYOSU_DELAY(), O const&, T0 const& t0, T1 const& t1, Ts const&... ts) noexcept
  {
    using r_t = kyosu::as_real_type_t<kyosu::as_cayley_dickson_like_t<T0, T1, Ts...>>;
    if constexpr (sizeof...(Ts) == 0) return kyosu::if_else(is_equal(t0, t1), kyosu::one(eve::as<r_t>()), zero);
    else
    {
      auto that = kronecker(t0, t1);
      ((that *= kronecker(t1, ts)), ...);
      return that;
    }
  }
}
