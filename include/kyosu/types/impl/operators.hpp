//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
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

  /// Identity for Caley-Dickinson value
  template<concepts::caley_dickinson Z>
  constexpr auto operator+(Z const& z) noexcept
  {
    return z;
  }

  /// Compute the negation of a given Caley-Dickinson value
  template<concepts::caley_dickinson Z>
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

  /// Returns the sum of a Caley-Dickinson value and a real value in any order
  template<eve::value T1, eve::value T2>
  requires(concepts::caley_dickinson<T1> || concepts::caley_dickinson<T2>)
  as_caley_dickinson_t<T1,T2> operator+(T1 const& a, T2 const& b) noexcept
  {
    as_caley_dickinson_t<T1,T2> that{a};
    return that += b;
  }

  /// Returns the difference of two Caley-Dickinson values
  template<eve::value T1, eve::value T2>
  requires(concepts::caley_dickinson<T1> || concepts::caley_dickinson<T2>)
  as_caley_dickinson_t<T1,T2> operator-(T1 const& a, T2 const& b) noexcept
  {
    as_caley_dickinson_t<T1,T2> that{a};
    return that -= b;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
