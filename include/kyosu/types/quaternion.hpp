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
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //! @typedef quaternion
  //! @brief Type alias for quaternion numbers
  //!
  //! Quaternion numbers are implemented as Caley-dickson numbers of dimension 4.
  //!
  //! @}
  //====================================================================================================================
  template<typename T>
  using quaternion = cayley_dickson<T,4>;

  template<typename T>
  using as_quaternion_t = as_cayley_dickson_n_t<4,T>;
}

#include <kyosu/functions/to_quaternion.hpp>
