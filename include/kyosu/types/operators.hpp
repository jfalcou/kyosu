//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/functions/convert.hpp>

namespace kyosu
{
  //====================================================================================================================
  //! @name Unary Operators
  //! @{
  //====================================================================================================================

  //! @brief Identity for Cayley-Dickson value
  //! @related cayley_dickson
  template<concepts::cayley_dickson Z>
  constexpr auto operator+(Z const& z) noexcept
  {
    return z;
  }

  //! @brief Compute the negation of a given Cayley-Dickson value
  //! @related cayley_dickson
  template<concepts::cayley_dickson Z>
  constexpr auto operator-(Z const& z) noexcept
  {
    return Z{kumi::map([](auto m) { return -m; }, z)};
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //====================================================================================================================
  //! @name Binary Operators
  //! @{
  //====================================================================================================================

  //! @brief Returns the sum of a Cayley-Dickson value and a real value in any order
  //! @related cayley_dickson
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator+(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that += b;
  }

  //! @brief  Returns the difference of two Cayley-Dickson values
  //! @related cayley_dickson
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator-(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that -= b;
  }

  //! @brief Returns the product of two Cayley-Dickson values
  //! @related cayley_dickson
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> && concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that *= b;
  }

  /// @overload
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> != concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    // This is ok as the non cayley-Dickson type is a scalar
    if constexpr(concepts::cayley_dickson<T1>)
    {
      using type = as_cayley_dickson_t<T1,T2>;
      type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
      return that *= b;
    }
    else
    {
      using type = as_cayley_dickson_t<T1,T2>;
      type that{kyosu::convert(b,eve::as<eve::element_type_t<type>>())};
      return that *= a;
    }
  }

  //! @brief Returns the ration of two Cayley-Dickson values
  //! @related cayley_dickson
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator/(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that /= b;
  }

  //! @brief Compares a Cayley-Dickson value and a real for equality
  //! @related cayley_dickson
  template<concepts::cayley_dickson T1, concepts::real T2>
  constexpr auto operator==( T1 const& a, T2 b)
  {
    using type = as_cayley_dickson_t<T1,T2>;
    return type{a}.contents == type{b}.contents;
  }

  //! @brief Compares a real and a Cayley-Dickson value for equality
  //! @related cayley_dickson
  template<concepts::real T1, concepts::cayley_dickson T2>
  constexpr auto operator==( T1 const& a, T2 b)
  {
    using type = as_cayley_dickson_t<T1,T2>;
    return type{a}.contents == type{b}.contents;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
