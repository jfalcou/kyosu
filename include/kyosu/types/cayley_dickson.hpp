//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/eve.hpp>
#include <kyosu/details/abi.hpp>
#include <kyosu/types/concepts.hpp>
#include <kyosu/types/traits.hpp>
#include <bit>

namespace kyosu
{
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //! @class cayley_dickson
  //! @brief Cayley-Dickson algebra main abstraction
  //! It is built so that all operation over C, Q and other such algebra can be done in a streamlined fashion
  //! based on the Cayley–Dickson construction.
  //====================================================================================================================
  template<eve::floating_scalar_value Type, unsigned int N>
  requires(N > 1 && std::has_single_bit(N))
  struct cayley_dickson
  {
    using underlying_type = Type;
    using is_cayley_dickson = void;

    static constexpr auto static_dimension = N;

    /// Default Cayley-Dickson constructor
    constexpr cayley_dickson() noexcept : contents{} {}

    /// Construct a Cayley-Dickson from a real value
    template<std::convertible_to<Type> T> constexpr cayley_dickson(T v) noexcept : contents{}
    {
      kumi::get<0>(contents) = v;
    }

    /// Construct a Cayley-Dickson instance from a sequences of real values
    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
    requires((1 + sizeof...(Ts)) <= static_dimension)
    constexpr cayley_dickson(T0 v0, Ts... vs) noexcept
      : contents(kumi::cat(kumi::tuple{static_cast<Type>(v0), static_cast<Type>(vs)...},
                           kumi::fill<(N - 1 - sizeof...(Ts))>(Type{0})))
    {
    }

    /// Construct a Cayley-Dickson instance from a properly sized product_type
    constexpr cayley_dickson(eve::sized_product_type<N> auto const& vs) : contents{vs} {}

    /// Constructs a Cayley-Dickson instance by aggregating two Cayley-Dickson of smaller dimension
    template<unsigned int M>
    requires(M > 1 && M == N / 2)
    constexpr cayley_dickson(cayley_dickson<Type, M> const& a, cayley_dickson<Type, M> const& b) noexcept
      : contents(kumi::cat(a.contents, b.contents))
    {
    }

    /// Constructs a Cayley-Dickson instance from an Cayley-Dickson of smaller dimension
    template<unsigned int M>
    requires(M > 1 && M == N / 2)
    constexpr cayley_dickson(cayley_dickson<Type, M> const& a) noexcept
    requires(N > 1)
      : contents(kumi::cat(a.contents, kumi::fill<M>(Type{0})))
    {
    }

    /// Assign a smaller Cayley-Dickson to another
    template<concepts::cayley_dickson T>
    constexpr cayley_dickson& operator=(T const& a) noexcept
    requires(T::static_dimension < N)
    {
      return (*this = cayley_dickson{a});
    }

    //==================================================================================================================
    // ++/--
    //==================================================================================================================

    //! Pre-incrementation operator
    KYOSU_FORCEINLINE auto& operator++() noexcept
    {
      kumi::get<0>(contents)++;
      return *this;
    }

    //! Pre-decrementation operator
    KYOSU_FORCEINLINE auto& operator--() noexcept
    {
      kumi::get<0>(contents)--;
      return *this;
    }

    //! Post-incrementation operator
    KYOSU_FORCEINLINE auto operator++(int) noexcept
    {
      auto that(*this);
      this->operator++();
      return that;
    }

    //! Post-decrementation operator
    KYOSU_FORCEINLINE auto operator--(int) noexcept
    {
      auto that(*this);
      this->operator--();
      return that;
    }

    //==================================================================================================================
    //  Tuple-like behavior
    //==================================================================================================================
    using data_type = kumi::result::fill_t<static_dimension, Type>;

    friend constexpr eve::as_logical_t<Type> operator==(cayley_dickson const& a, cayley_dickson const& b) noexcept
    {
      return a.contents == b.contents;
    }

    friend constexpr eve::as_logical_t<Type> operator!=(cayley_dickson const& a, cayley_dickson const& b) noexcept
    {
      return a.contents != b.contents;
    }

    data_type contents;
  };

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  template<std::size_t I, typename T, unsigned int N> constexpr auto& get(cayley_dickson<T, N>& c) noexcept
  {
    return kumi::get<I>(c.contents);
  }

  template<std::size_t I, typename T, unsigned int N> constexpr auto get(cayley_dickson<T, N> const& c) noexcept
  {
    return kumi::get<I>(c.contents);
  }

  //====================================================================================================================
  //! @name Deduction Guides
  //! @related cayley_dickson
  //! @{
  //====================================================================================================================
  /// Deduction guide for constructing from product type
  template<eve::product_type Tuple>
  cayley_dickson(Tuple const&) -> cayley_dickson<kumi::element_t<0, Tuple>, kumi::size_v<Tuple>>;

  /// Deduction guide for constructing from sequence of values
  template<typename T0, std::convertible_to<T0>... Ts>
  cayley_dickson(T0, Ts...) -> cayley_dickson<T0, 1 + sizeof...(Ts)>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}

namespace kyosu::_
{
  template<typename T, unsigned int N> inline constexpr unsigned int rank<cayley_dickson<T, N>> = N;

  template<typename T, unsigned int N, typename L>
  inline constexpr unsigned int rank<eve::wide<cayley_dickson<T, N>, L>> = N;
}

#if !defined(KYOSU_DOXYGEN_INVOKED)
// std::tuple adaptation
template<typename T, unsigned int N>
struct std::tuple_size<kyosu::cayley_dickson<T, N>> : std::integral_constant<std::size_t, N>
{
};

template<typename T, unsigned int N, std::size_t I> struct std::tuple_element<I, kyosu::cayley_dickson<T, N>>
{
  using type = T;
};

#endif

#include <kyosu/types/io.hpp>
#include <kyosu/types/compounds.hpp>
#include <kyosu/types/operators.hpp>
