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
  //  cyl_lbessel_i0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_lbessel_i0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_lbessel_in(0, z);
    }
    else
    {
      return cayley_extend(cyl_lbessel_i0, z);
    }
  }
}
