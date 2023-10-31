//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/besselj0.hpp>
#include <kyosu/types/impl/detail/bessely0.hpp>
#include <kyosu/types/impl/detail/bessely1.hpp>

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
      return cayley_extend_rev(cyl_bessel_h1n, n, z);
    }
  }
}
