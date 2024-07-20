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

  /// Identity for Cayley-dickson value
  template<concepts::cayley_dickson Z>
  constexpr auto operator+(Z const& z) noexcept
  {
    return z;
  }

  /// Compute the negation of a given Cayley-dickson value
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

  /// Returns the sum of a Cayley-dickson value and a real value in any order
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  auto operator+(T1 const& a, T2 const& b) noexcept -> as_cayley_dickson_t<T1,T2>
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that += b;
  }

  /// Returns the difference of two Cayley-dickson values
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator-(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that -= b;
  }

  /// Returns the product of two Cayley-dickson values
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> && concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that *= b;
  }

  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> != concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    // This is ok as the non cayley-dickson type is a scalar
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

  /// Returns the ration of two Cayley-dickson values
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator/(T1 const& a, T2 const& b) noexcept
  {
    using type = as_cayley_dickson_t<T1,T2>;
    type that{kyosu::convert(a,eve::as<eve::element_type_t<type>>())};
    return that /= b;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
