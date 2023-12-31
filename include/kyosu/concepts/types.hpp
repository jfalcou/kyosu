//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits.hpp>
#include <type_traits>

namespace kyosu::concepts
{
  /// General Caley-dickson concept
  template<typename T>
  concept cayley_dickson = requires(T const&)
  {
    typename eve::element_type_t<std::remove_cvref_t<T>>::is_cayley_dickson;
  };

  /// Complex number concept
  template<typename T>
  concept complex     = cayley_dickson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_size == 2;

  /// Quaternion concept
  template<typename T>
  concept quaternion  = cayley_dickson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_size == 4;

  /// Octonion concept
  template<typename T>
  concept octonion    = cayley_dickson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_size == 8;
}
