//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/types/caley_dickinson.hpp>
#include <eve/concept/value.hpp>

namespace kyosu::concepts
{
  template<typename T>
  concept octonion = caley_dickinson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_size == 8;
}

namespace kyosu
{
  template<typename T>
  using octonion = caley_dickinson<T,8>;
}
