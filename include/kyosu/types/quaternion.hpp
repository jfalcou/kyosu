//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/types/cayley_dickson.hpp>
#include <eve/concept/value.hpp>

namespace kyosu
{
  template<typename T>
  using quaternion = cayley_dickson<T,4>;

  template<typename T>
  using as_quaternion_t = as_cayley_dickson_n_t<4,T>;
}
