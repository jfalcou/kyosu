//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <kyosu/concepts.hpp>
#include <bit>

namespace kyosu
{
  //====================================================================================================================
  // caley_dickinson struct is the bare bone support class for complex, quaternion and above.
  // It is built so that all operation over C, Q and other such algebra can be done in a streamlined fashion
  // based on the Caley-Dickinson scheme.
  //====================================================================================================================
  template<eve::floating_scalar_value Type, unsigned int N>
  requires(N> 1 && std::has_single_bit(N))
  struct caley_dickinson
  {
    using is_caley_dickinson  = void;

    static constexpr auto static_size =  N;

    using underlying_type = Type;

    constexpr caley_dickinson() noexcept : contents{} {}

    template<unsigned int M>
    requires(M > 1 && M == N/2)
    constexpr caley_dickinson(caley_dickinson<Type,M> const& a, caley_dickinson<Type,M> const& b) noexcept
            : contents(kumi::cat(a.contents,b.contents))
    {}

    template<unsigned int M>
    requires(M > 1 && M == N/2)
    constexpr caley_dickinson(caley_dickinson<Type,M> const& a) noexcept requires(N>1)
            : contents(kumi::cat(a.contents, kumi::generate<M>(Type{0}) ))
    {}

    template<concepts::caley_dickinson T>
    requires(T::static_size<N)
    constexpr caley_dickinson& operator=( T const& a) noexcept
    {
      *this = caley_dickinson{a};
      return *this;
    }

    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
    requires( (1+sizeof...(Ts)) <= static_size && std::has_single_bit(1+sizeof...(Ts)) )
    constexpr caley_dickinson(T0 v0, Ts... vs) noexcept
            : contents(kumi::cat( kumi::tuple{static_cast<Type>(v0),static_cast<Type>(vs)...}
                                , kumi::generate<(N-1-sizeof...(Ts))>(Type{0})
                      )         )
    {}

    template<std::convertible_to<Type> T>
    constexpr caley_dickinson(T v) noexcept : contents{}
    {
      get<0>(contents) = v;
    }

    /// Construct a Caley-Dickinson abstraction from a properly sized product_type
    constexpr caley_dickinson(kumi::sized_product_type<N> auto const& vs) : contents{vs} {}

    //==================================================================================================================
    //  Tuple-like behavior
    //==================================================================================================================
    using data_type       = kumi::result::generate_t<static_size,underlying_type>;
    using is_product_type = void;

    template<std::size_t I>
    friend constexpr auto& get(caley_dickinson& c) noexcept { return get<I>(c.contents); }

    template<std::size_t I>
    friend constexpr auto get(caley_dickinson const& c) noexcept { return get<I>(c.contents); }

    friend constexpr bool operator==(caley_dickinson const&, caley_dickinson const&) noexcept =default;

    data_type contents;
  };

  template<typename Tag, concepts::caley_dickinson Z>
  EVE_FORCEINLINE constexpr auto tagged_dispatch(Tag const&, eve::as<Z> const&) noexcept
  {
    eve::detail::callable_object<Tag> cst;
    return  Z(cst(eve::as<typename Z::value_type>{}));
  }

  //====================================================================================================================
  //! @name Deduction Guides
  //! @{
  //====================================================================================================================
  /// Deduction guide for constructing from product type
  template<kumi::product_type Tuple>
  caley_dickinson(Tuple const&) -> caley_dickinson<kumi::element_t<0,Tuple>, kumi::size_v<Tuple>>;

  /// Deduction guide for constructing from sequence of values
  template<typename T0, std::convertible_to<T0>... Ts>
  caley_dickinson(T0,Ts... ) -> caley_dickinson<T0,1+sizeof...(Ts)>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}

#if !defined(KYOSU_DOXYGEN_INVOKED)
// std::tuple adaptation
template<typename T, unsigned int N>
struct std::tuple_size<kyosu::caley_dickinson<T,N>> : std::integral_constant<std::size_t,N> {};

template<typename T, unsigned int N, std::size_t I>
struct std::tuple_element<I, kyosu::caley_dickinson<T,N>>
{
  using type = T;
};
#endif

#include <kyosu/types/traits.hpp>
#include <kyosu/types/impl/io.hpp>
#include <kyosu/types/impl/compounds.hpp>
#include <kyosu/types/impl/operators.hpp>
