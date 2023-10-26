//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
//#include <kyosu/types/impl/bessel.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_lbessel_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_lbessel_j0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return log(cyl_bessel_j0(z));
    }
    else
    {
      return cayley_extend(cyl_bessel_j0, z);
    }
  }
}
