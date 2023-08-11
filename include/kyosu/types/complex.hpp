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

namespace kyosu
{
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //! @typedef complex
  //! @brief Type alias for complex numbers
  //!
  //! Complex numbers are implemented as Caley-Dickinson numbers of dimension 2.
  //!
  //! @}
  //====================================================================================================================
  template<typename T>
  using complex     = caley_dickinson<T,2>;

  template<typename T>
  using as_complex_t = as_caley_dickinson_n_t<2,T>;
}
