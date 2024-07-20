//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/types/cayley_dickson.hpp>
#include <kyosu/types/traits.hpp>

namespace kyosu
{
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //! @typedef complex_t
  //! @brief Type alias for complex numbers
  //!
  //! Complex numbers are implemented as Cayley-dickson numbers of dimension 2.
  //!
  //! @}
  //====================================================================================================================

  template<typename T>
  using complex_t = as_cayley_dickson_n_t<2,T>;
}
