//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/scalar.hpp>
#include <eve/concept/same_lanes.hpp>
#include <eve/traits/element_type.hpp>
#include <type_traits>

namespace kyosu::concepts
{
  /// General Cayley-dickson concept
  template<typename T>
  concept cayley_dickson = requires(T const&)
  {
    typename eve::element_type_t<std::remove_cvref_t<T>>::is_cayley_dickson;
  };

  template<typename T>
  concept scalar_cayley_dickson = cayley_dickson<T> && eve::scalar_value<T>;

  /// General real concept
  template<typename T>
  concept real = std::is_arithmetic_v<eve::element_type_t<std::remove_cvref_t<T>>>;

  template<typename T>
  concept scalar_real = real<T> && eve::scalar_value<T>;

  /// Complex number concept
  template<typename T>
  concept complex     = cayley_dickson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_dimension == 2;

  /// Quaternion concept
  template<typename T>
  concept quaternion  = cayley_dickson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_dimension == 4;

  /// Octonion concept
  template<typename T>
  concept octonion    = cayley_dickson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_dimension == 8;
}
