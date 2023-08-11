//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace kyosu
{
  //====================================================================================================================
  //! @name Compound Assignment Operators
  //! @{
  //====================================================================================================================

  /// Adds the real value `other` to `self` and returns the new value of `self`.
  constexpr auto& operator+=(concepts::caley_dickinson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) += other;} )
  {
    kumi::get<0>(self) += other;
    return self;
  }

  /// Adds the Caley-Dickinson value `other` to `self` and returns the new value of `self`.
  template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  requires(dimension_v<Other> <= dimension_v<Self>)
  constexpr auto& operator+=(Self& self, Other const& other) noexcept
  {
    kumi::for_each_index( [&]<typename I>(I,auto const& o) { kumi::get<I::value>(self) += o; }, other);
    return self;
  }

  /// Substracts the real value `other` from `self` and returns the new value of `self`.
  constexpr auto& operator-=(concepts::caley_dickinson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) -= other;} )
  {
    kumi::get<0>(self) -= other;
    return self;
  }

  /// Substracts the Caley-Dickinson value `other` from `self` and returns the new value of `self`.
  template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  requires(dimension_v<Other> <= dimension_v<Self>)
  constexpr auto& operator-=(Self& self, Other const& other) noexcept
  {
    kumi::for_each_index( [&]<typename I>(I,auto const& o) { kumi::get<I::value>(self) -= o; }, other);
    return self;
  }

  /// Multiplies `self` by the  real value `other`  and returns the new value of `self`.
  constexpr auto& operator*=(concepts::caley_dickinson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) *= other;} )
  {
    kumi::get<0>(self) *= other;
    return self;
  }

  // /// Multiplies `self` by the Caley-Dickinson value `other`  and returns the new value of `self`.
  // template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  // requires(dimension_v<Other> <= dimension_v<Self>)
  // constexpr auto& operator*=(Self& self, Other const& other) noexcept
  // {
  //   return self;
  // }

  /// Divides `self` by the  real value `other` and returns the new value of `self`.
  constexpr auto& operator/=(concepts::caley_dickinson auto& self, eve::ordered_value auto other) noexcept
  requires( requires {get<0>(self) /= other;} )
  {
    kumi::get<0>(self) /= other;
    return self;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //====================================================================================================================
  //  Requirements traps
  //  If a compilation error occurs and references one of those overloads, this means you tried to call an operator
  //  in an incorrect setup like:
  //    * compound assignment between a scalar and a wide (like Complex += Wide)
  //    * compound assignment between two Caley-Dickinson of incompatible dimension_v (like Complex += Quaternion)
  //====================================================================================================================
#if !defined(KYOSU_DOXYGEN_INVOKED)
  template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator+=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator+=(concepts::caley_dickinson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) += v;} ) = delete;

  template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator-=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator-=(concepts::caley_dickinson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) -= v;} ) = delete;

  template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator*=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator*=(concepts::caley_dickinson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) *= v;} ) = delete;

  template<concepts::caley_dickinson Self, concepts::caley_dickinson Other>
  requires(dimension_v<Other> > dimension_v<Self>)
  constexpr auto& operator/=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator/=(concepts::caley_dickinson auto& self, eve::ordered_value auto v) noexcept
  requires( !requires {get<0>(self) /= v;} ) = delete;
#endif
}
