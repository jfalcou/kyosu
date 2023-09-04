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
#include <kyosu/functions.hpp>
#include <kyosu/types/traits.hpp>
#include <kyosu/types/impl/arithmetic.hpp>
#include <kyosu/types/impl/predicates.hpp>
#include <kyosu/types/impl/math.hpp>
#include <kyosu/types/impl/trigo.hpp>
#include <kyosu/types/impl/complex/predicates.hpp>
#include <kyosu/types/impl/complex/arithmetic.hpp>

#include <bit>

namespace kyosu
{
  //====================================================================================================================
  // cayley_dickson struct is the bare bone support class for complex, quaternion and above.
  // It is built so that all operation over C, Q and other such algebra can be done in a streamlined fashion
  // based on the Cayley–Dickson construction.
  //====================================================================================================================
  template<eve::floating_scalar_value Type, unsigned int N>
  requires(N> 1 && std::has_single_bit(N))
  struct cayley_dickson
  {
    using is_cayley_dickson  = void;

    static constexpr auto static_size =  N;

    using underlying_type = Type;

    constexpr cayley_dickson() noexcept : contents{} {}

    template<unsigned int M>
    requires(M > 1 && M == N/2)
    constexpr cayley_dickson(cayley_dickson<Type,M> const& a, cayley_dickson<Type,M> const& b) noexcept
            : contents(kumi::cat(a.contents,b.contents))
    {}

    template<unsigned int M>
    requires(M > 1 && M == N/2)
    constexpr cayley_dickson(cayley_dickson<Type,M> const& a) noexcept requires(N>1)
            : contents(kumi::cat(a.contents, kumi::generate<M>(Type{0}) ))
    {}

    template<concepts::cayley_dickson T>
    requires(T::static_size<N)
    constexpr cayley_dickson& operator=( T const& a) noexcept
    {
      *this = cayley_dickson{a};
      return *this;
    }

    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
    requires( (1+sizeof...(Ts)) <= static_size )
    constexpr cayley_dickson(T0 v0, Ts... vs) noexcept
            : contents(kumi::cat( kumi::tuple{static_cast<Type>(v0),static_cast<Type>(vs)...}
                                , kumi::generate<(N-1-sizeof...(Ts))>(Type{0})
                      )         )
    {}

    template<std::convertible_to<Type> T>
    constexpr cayley_dickson(T v) noexcept : contents{}
    {
      kumi::get<0>(contents) = v;
    }

    /// Construct a Caley-dickson abstraction from a properly sized product_type
    constexpr cayley_dickson(kumi::sized_product_type<N> auto const& vs) : contents{vs} {}

    //==================================================================================================================
    // ++/--
    //==================================================================================================================

    //! Pre-incrementation operator
    KYOSU_FORCEINLINE auto& operator++() noexcept { kumi::get<0>(contents)++; return *this; }

    //! Pre-decrementation operator
    KYOSU_FORCEINLINE auto& operator--() noexcept { kumi::get<0>(contents)--; return *this; }

    //! Post-incrementation operator
    KYOSU_FORCEINLINE auto operator++(int) noexcept
    {
      auto  that(*this);
      this->operator++();
      return that;
    }

    //! Post-decrementation operator
    KYOSU_FORCEINLINE auto operator--(int) noexcept
    {
      auto  that(*this);
      this->operator--();
      return that;
    }

    //==================================================================================================================
    //  Tuple-like behavior
    //==================================================================================================================
    using data_type       = kumi::result::generate_t<static_size,underlying_type>;
    using is_product_type = void;

    friend constexpr bool operator==(cayley_dickson const&, cayley_dickson const&) noexcept =default;

    data_type contents;
  };

  template<std::size_t I, typename T, unsigned int N>
  constexpr auto& get(cayley_dickson<T,N>& c) noexcept { return kumi::get<I>(c.contents); }

  template<std::size_t I, typename T, unsigned int N>
  constexpr auto get(cayley_dickson<T,N> const& c) noexcept { return kumi::get<I>(c.contents); }

  //==================================================================================================================
  // Main function dispatchers
  //==================================================================================================================
  template<typename... T>
  requires(concepts::cayley_dickson<T> || ... )
  KYOSU_FORCEINLINE   constexpr auto tag_invoke(eve::callable auto const& f, auto, T&&... c) noexcept
                  ->  decltype(_::dispatch(f, KYOSU_FWD(c)...))
  {
    return _::dispatch(f, KYOSU_FWD(c)...);
  }

  //==================================================================================================================
  //  Tag invoke override for if_else - Outside so it can properly deals with the complicated parameters of if_else
  //==================================================================================================================
  template<typename T, typename F>
  requires(concepts::cayley_dickson<T> || concepts::cayley_dickson<F>)
  KYOSU_FORCEINLINE constexpr auto  tag_invoke( eve::tag_of<kyosu::if_else> const& fn, auto, auto m
                                              , T const& t, F const& f
                                              ) noexcept
                -> decltype(_::dispatch(fn, m, t, f))
  {
    return _::dispatch(fn, m,t,f);
  }

  template<concepts::cayley_dickson T, eve::value C>
  requires( eve::scalar_value<T> )
  KYOSU_FORCEINLINE
  constexpr auto tag_invoke( eve::tag_of<kyosu::convert> const& f, auto, C const& c, eve::as<T> const& tgt) noexcept
                -> decltype(_::dispatch(f, c, tgt))
  {
    return _::dispatch(f, c, tgt);
  }

  //==================================================================================================================
  //  Tag invoke override for parts extraction - Outside so they can see get<I>(c)
  //==================================================================================================================
  template<concepts::extractor T, concepts::cayley_dickson C>
  KYOSU_FORCEINLINE constexpr decltype(auto)
  tag_invoke(T const&, auto, C&& c) noexcept
  {
    constexpr auto sz = eve::element_type_t<std::remove_cvref_t<C>>::static_size;

    if constexpr(T::minimum_valid_index == T::maximum_valid_index)
    {
      if constexpr(sz > T::minimum_valid_index) return get<T::minimum_valid_index>(EVE_FWD(c));
      else                                      return eve::underlying_type_t<std::remove_cvref_t<C>>{0};
    }
    else
    {
      auto parts = [&]()
      {
        auto idx = kumi::index<T::minimum_valid_index>;
        if constexpr(T::maximum_valid_index == -1)  return kumi::extract(c, idx);
        else                                        return kumi::extract(c, idx, kumi::index<T::maximum_valid_index>);
      }();

      return kumi::apply([](auto... e) { return eve::zip(e...); }, parts);
    }
  }

  // TODO: Move to tag_invoke when EVE catch up on this front
  template<typename Tag, eve::floating_scalar_value Type, unsigned int N>
  KYOSU_FORCEINLINE constexpr auto tagged_dispatch(Tag const&, eve::as<cayley_dickson<Type,N>> const&) noexcept
  {
    eve::detail::callable_object<Tag> cst;
    return cayley_dickson<Type,N>( cst(eve::as<Type>{}) );
  }

  //====================================================================================================================
  //! @name Deduction Guides
  //! @{
  //====================================================================================================================
  /// Deduction guide for constructing from product type
  template<kumi::product_type Tuple>
  cayley_dickson(Tuple const&) -> cayley_dickson<kumi::element_t<0,Tuple>, kumi::size_v<Tuple>>;

  /// Deduction guide for constructing from sequence of values
  template<typename T0, std::convertible_to<T0>... Ts>
  cayley_dickson(T0,Ts... ) -> cayley_dickson<T0,1+sizeof...(Ts)>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}

#if !defined(KYOSU_DOXYGEN_INVOKED)
// std::tuple adaptation
template<typename T, unsigned int N>
struct std::tuple_size<kyosu::cayley_dickson<T,N>> : std::integral_constant<std::size_t,N> {};

template<typename T, unsigned int N, std::size_t I>
struct std::tuple_element<I, kyosu::cayley_dickson<T,N>>
{
  using type = T;
};

template<typename Wrapper, typename T, unsigned int N>
struct eve::supports_like<Wrapper,kyosu::cayley_dickson<T,N>>
      : std::bool_constant<   kyosu::concepts::cayley_dickson<Wrapper>
                          ||  std::same_as<T, eve::element_type_t<Wrapper>>
                          ||  plain_scalar_value<Wrapper>
                          >
{
};
#endif

#include <kyosu/types/impl/io.hpp>
#include <kyosu/types/impl/compounds.hpp>
#include <kyosu/types/impl/operators.hpp>
#include <kyosu/types/impl/reals.hpp>
