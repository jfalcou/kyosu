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

namespace kyosu
{
  template<typename Options>
  struct kolmmean_t : eve::strict_elementwise_callable<kolmmean_t, Options, eve::pedantic_option, eve::kahan_option>
  {
    template<typename... Ts> struct result : as_cayley_dickson<Ts...>
    {
    };
    template<concepts::real... Ts> struct result<Ts...> : eve::common_value<Ts...>
    {
    };

    template<typename F, typename G, concepts::cayley_dickson_like... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    KYOSU_FORCEINLINE constexpr typename result<Ts...>::type operator()(F f, G g, Ts... ts) const noexcept
    {
      return KYOSU_CALL(f, g, ts...);
    }

    template<typename F, typename G, eve::concepts::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !concepts::cayley_dickson_like<Tup>)
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<result, Tup> operator()(F f, G g, Tup const& t) const noexcept
    requires(kumi::size_v<Tup> >= 1)
    {
      return KYOSU_CALL(f, g, t);
    }

    KYOSU_CALLABLE_OBJECT(kolmmean_t, kolmmean_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var kolmmean
  //!   @brief Callable object computing the 'Kolmogorov-Nagumo-de Finetti' mean of the inputs:
  //!   \f$ \mathbf{g}(\mathbf{average}\mathbf{f}(x_s)) \f$.
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
  //!      constexpr auto kolmmean(auto ... xs)                                              noexcept; // 1
  //!      constexpr auto kolmmean(eve::concepts::non_empty_product_type auto const& tup)             noexcept; // 2
  //!      conséexpr auto kolmmean[pedantic](/*any of the above overloads*/)                 noexcept; // 3
  //!      constexpr auto kolmmean[kahan] (/*any of the above overloads*/)                   noexcept; // 4
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
  //!     1. The value of the quasi arithmetic mean of the arguments is returned.
  //!     2. The value of the guasi arithmetic mean of the tuple elements is returned.
  //!     3. avoid spurious overflows on average.
  //!     4. kahan algorithm is used to enhance accuracy.
  //!
  //!  @note For the result to be a proper kolmogorov mean, `f` must be mathematically continuous and injective and `g` be its inverse.
  //!        and **KYOSU** need them to be defined for a cayley_dickson_like input, and returning the same type.
  //!        However \f$ \mathbf{g}(\sum \mathbf{f}(x_s)) \f$ is returned if computable. However for one parameter only, the call always
  //!        returns the parameter itself.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/kolmmean.cpp}
  //======================================================================================================================
  inline constexpr auto kolmmean = eve::functor<kolmmean_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{

  template<typename F,
           typename G,
           concepts::cayley_dickson_like T0,
           concepts::cayley_dickson_like... Ts,
           eve::callable_options O>
  EVE_FORCEINLINE constexpr auto kolmmean_(KYOSU_DELAY(), O const& o, F f, G g, T0 t0, Ts... args) noexcept
  {
    if constexpr (sizeof...(Ts) == 0) return t0;
    else return g(average[o](f(t0), f(args)...));
  }

  template<typename F, typename G, eve::concepts::non_empty_product_type Tup, eve::callable_options O>
  EVE_FORCEINLINE constexpr auto kolmmean_(KYOSU_DELAY(), O const& o, F f, G g, Tup tup) noexcept
  requires(!concepts::cayley_dickson_like<Tup>)
  {
    return kumi::map([f, g](auto... m) { return kolmmean(f, g, m...); }, tup);
  }
}
