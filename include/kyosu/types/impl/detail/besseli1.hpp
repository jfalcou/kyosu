//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/besselj1.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_i1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto [r, i] = cyl_bessel_j1(complex(-ipart(z), real(z)));
      return complex(i, -r);
    }
    else
    {
      return cayley_extend(cyl_bessel_i1, z);
    }
  }
}
