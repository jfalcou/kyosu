//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/scalar.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/same_lanes.hpp>
#include <eve/traits/element_type.hpp>
#include <type_traits>

namespace kyosu::_
{
  template<typename T>                    inline constexpr unsigned int rank = 0;
  template<eve::floating_value T>         inline constexpr unsigned int rank<T> = 1;
  template<eve::integral_scalar_value T>  inline constexpr unsigned int rank<T> = 1;
}

namespace kyosu::concepts
{
  // Value of the Cayley-Dickson algebra encompass reals and
  // actual caley-dickson values
  template<typename T>
  concept cayley_dickson_like = _::rank<std::remove_cvref_t<T>> != 0;

  template<typename T>
  concept complex_like = cayley_dickson_like<T> && _::rank<std::remove_cvref_t<T>> <= 2;

  template<typename T>
  concept quaternion_like = cayley_dickson_like<T> && _::rank<std::remove_cvref_t<T>> <= 4;

  template<typename T>
  concept octonion_like = cayley_dickson_like<T> && _::rank<std::remove_cvref_t<T>> <= 8;

  /// General Cayley-dickson concept
  template<typename T>
  concept cayley_dickson = cayley_dickson_like<T> &&  _::rank<std::remove_cvref_t<T>> > 1;

  template<typename T>
  concept scalar_cayley_dickson = cayley_dickson<T> && eve::scalar_value<T>;

  /// General real concept
  template<typename T>
  concept real = cayley_dickson_like<T> && _::rank<std::remove_cvref_t<T>> == 1;

  template<typename T>
  concept scalar_real = real<T> && eve::scalar_value<T>;

  /// Complex number concept
  template<typename T>
  concept complex     = cayley_dickson<T> && _::rank<std::remove_cvref_t<T>> == 2;

  /// Quaternion concept
  template<typename T>
  concept quaternion  = cayley_dickson<T> && _::rank<std::remove_cvref_t<T>> == 4;

  /// Octonion concept
  template<typename T>
  concept octonion    = cayley_dickson<T> && _::rank<std::remove_cvref_t<T>> == 8;
}
