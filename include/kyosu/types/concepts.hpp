//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

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

  /// General real concept
  template<typename T>
  concept real = std::is_arithmetic_v<eve::element_type_t<T>>;

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
