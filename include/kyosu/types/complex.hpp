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
  concept complex = caley_dickinson<T> && eve::element_type_t<std::remove_cvref_t<T>>::static_size == 2;
}

namespace kyosu
{
  template<typename T>
  using complex     = caley_dickinson<T,2>;

  template<typename T>
  using as_complex_t = as_caley_dickinson_n_t<2,T>;
}
