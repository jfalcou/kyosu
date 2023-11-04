//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_j.hpp>
#include <kyosu/types/impl/detail/bessely0.hpp>
#include <kyosu/types/impl/detail/bessely1.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_yn
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_yn>, int nn, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto y = cyl_bessel_y0(z);
    if (nn != 0)
    {
      auto n = eve::abs(nn);
      auto js = Js(n, z);
      using u_t   =  eve::underlying_type_t<Z>;
      auto twoopi = eve::two_o_pi(eve::as<u_t>());
      for(int i=1; i <= n ; ++i)
      {
        y = (js[i]*y-twoopi*rec(z))/js[i-1];
      }
      auto r = if_else(eve::is_gtz(real(z)) && is_real(z) && is_nan(y), complex(real(y)), y);
      r = if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), r);
      return nn < 0 ? r*eve::sign_alternate(u_t(n)) : r;
    }
    else return y;
  }
}
