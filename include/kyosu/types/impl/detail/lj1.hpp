//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/ljn.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_lbessel_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_lbessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_lbessel_jn(1, z);
    }
    else
    {
      return cayley_extend(cyl_bessel_j1, z);
    }
  }
}
