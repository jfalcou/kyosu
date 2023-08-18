//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace kyosu
{
  //====================================================================================================================
  //! @name Unary Operators
  //! @{
  //====================================================================================================================

  /// Identity for Caylay-dickson value
  template<concepts::cayley_dickson Z>
  constexpr auto operator+(Z const& z) noexcept
  {
    return z;
  }

  /// Compute the negation of a given Caylay-dickson value
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

  /// Returns the sum of a Caylay-dickson value and a real value in any order
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator+(T1 const& a, T2 const& b) noexcept
  {
    as_cayley_dickson_t<T1,T2> that{a};
    return that += b;
  }

  /// Returns the difference of two Caylay-dickson values
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> || concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator-(T1 const& a, T2 const& b) noexcept
  {
    as_cayley_dickson_t<T1,T2> that{a};
    return that -= b;
  }

  // Returns the product of two Caylay-dickson values
  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> && concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    as_cayley_dickson_t<T1,T2> that{a};
    return that *= b;
  }

  template<eve::value T1, eve::value T2>
  requires(concepts::cayley_dickson<T1> != concepts::cayley_dickson<T2>)
  as_cayley_dickson_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    // This is ok as the non cayley-dickson type is a scalar
    if constexpr(concepts::cayley_dickson<T1>)
    {
      as_cayley_dickson_t<T1,T2> that{a};
      return that *= b;
    }
    else
    {
      as_cayley_dickson_t<T1,T2> that{b};
      return that *= a;
    }
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
