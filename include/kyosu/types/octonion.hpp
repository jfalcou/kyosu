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
  //! @addtogroup types
  //! @{
  //! @typedef octonion_t
  //! @brief Type alias for quaternion numbers
  //!
  //! Quaternion numbers are implemented as Caley-dickson numbers of dimension 4.
  //!
  //! @}
  //====================================================================================================================

  template<typename T>
  using octonion_t = as_cayley_dickson_n_t<8,T>;
}
