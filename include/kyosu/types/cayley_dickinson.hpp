//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <kyosu/concepts.hpp>
#include <bit>

namespace kyosu
{
  namespace tags
  {
    struct callable_jpart;
  }

  //====================================================================================================================
  // cayley_dickinson struct is the bare bone support class for complex, quaternion and above.
  // It is built so that all operation over C, Q and other such algebra can be done in a streamlined fashion
  // based on the Cayley–Dickson construction.
  //====================================================================================================================
  template<eve::floating_scalar_value Type, unsigned int N>
  requires(N> 1 && std::has_single_bit(N))
  struct cayley_dickinson
  {
    using is_cayley_dickinson  = void;

    static constexpr auto static_size =  N;

    using underlying_type = Type;

    constexpr cayley_dickinson() noexcept : contents{} {}

    template<unsigned int M>
    requires(M > 1 && M == N/2)
    constexpr cayley_dickinson(cayley_dickinson<Type,M> const& a, cayley_dickinson<Type,M> const& b) noexcept
            : contents(kumi::cat(a.contents,b.contents))
    {}

    template<unsigned int M>
    requires(M > 1 && M == N/2)
    constexpr cayley_dickinson(cayley_dickinson<Type,M> const& a) noexcept requires(N>1)
            : contents(kumi::cat(a.contents, kumi::generate<M>(Type{0}) ))
    {}

    template<concepts::cayley_dickinson T>
    requires(T::static_size<N)
    constexpr cayley_dickinson& operator=( T const& a) noexcept
    {
      *this = cayley_dickinson{a};
      return *this;
    }

    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
    requires( (1+sizeof...(Ts)) <= static_size )
    constexpr cayley_dickinson(T0 v0, Ts... vs) noexcept
            : contents(kumi::cat( kumi::tuple{static_cast<Type>(v0),static_cast<Type>(vs)...}
                                , kumi::generate<(N-1-sizeof...(Ts))>(Type{0})
                      )         )
    {}

    template<std::convertible_to<Type> T>
    constexpr cayley_dickinson(T v) noexcept : contents{}
    {
      kumi::get<0>(contents) = v;
    }

    /// Construct a Caylay-Dickinson abstraction from a properly sized product_type
    constexpr cayley_dickinson(kumi::sized_product_type<N> auto const& vs) : contents{vs} {}

    //==================================================================================================================
    //  Tag invoke override
    //==================================================================================================================
    // EVE_FORCEINLINE friend constexpr decltype(auto)
    // tag_invoke(kyosu::tags::callable_jpart const&, auto, eve::like<cayley_dickinson> auto&& c) noexcept
    // {
    //   if constexpr(N>=4)  return get<2>(EVE_FWD(c));
    //   else                return Type{0};
    // }

    //==================================================================================================================
    //  Tuple-like behavior
    //==================================================================================================================
    using data_type       = kumi::result::generate_t<static_size,underlying_type>;
    using is_product_type = void;

    template<std::size_t I>
    friend constexpr auto& get(cayley_dickinson& c) noexcept { return kumi::get<I>(c.contents); }

    template<std::size_t I>
    friend constexpr auto get(cayley_dickinson const& c) noexcept { return kumi::get<I>(c.contents); }

    friend constexpr bool operator==(cayley_dickinson const&, cayley_dickinson const&) noexcept =default;

    data_type contents;
  };

  template<typename Tag, concepts::cayley_dickinson Z>
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
  cayley_dickinson(Tuple const&) -> cayley_dickinson<kumi::element_t<0,Tuple>, kumi::size_v<Tuple>>;

  /// Deduction guide for constructing from sequence of values
  template<typename T0, std::convertible_to<T0>... Ts>
  cayley_dickinson(T0,Ts... ) -> cayley_dickinson<T0,1+sizeof...(Ts)>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}

#if !defined(KYOSU_DOXYGEN_INVOKED)
// std::tuple adaptation
template<typename T, unsigned int N>
struct std::tuple_size<kyosu::cayley_dickinson<T,N>> : std::integral_constant<std::size_t,N> {};

template<typename T, unsigned int N, std::size_t I>
struct std::tuple_element<I, kyosu::cayley_dickinson<T,N>>
{
  using type = T;
};

template<typename Wrapper, typename T, unsigned int N>
struct eve::supports_like<Wrapper,kyosu::cayley_dickinson<T,N>>
      : std::bool_constant<   std::same_as<kyosu::cayley_dickinson<T,N>, element_type_t<Wrapper>>
                          ||  std::same_as<T, element_type_t<Wrapper>>
                          ||  plain_scalar_value<Wrapper>
                          >
{
};
#endif

#include <kyosu/types/traits.hpp>
#include <kyosu/types/impl/io.hpp>
#include <kyosu/types/impl/compounds.hpp>
#include <kyosu/types/impl/operators.hpp>
