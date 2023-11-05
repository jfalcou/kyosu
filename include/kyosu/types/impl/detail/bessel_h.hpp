//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_j.hpp>
#include <kyosu/types/impl/detail/bessel_y.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h1n
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h1n>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      auto muli = [](auto z){ auto [r, i] = z; return complex(-i, r); };
      return  cyl_bessel_jn(n, z)+muli(cyl_bessel_yn(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1n, n, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h2n>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      auto muli = [](auto z){ auto [r, i] = z; return complex(-i, r); };
      return  cyl_bessel_jn(n, z)-muli(cyl_bessel_yn(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h2n, n, z);
    }
  }
}
