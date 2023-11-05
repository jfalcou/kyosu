//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_j.hpp>

namespace kyosu::_
{

  template < typename Z> struct mkjs
  {
    mkjs(size_t n, Z z):
      rz(kyosu::rec(z)),
      rs(kyosu::_:: R(n, z)),
      j(kyosu::cyl_bessel_jn(n, z)),
      i(n-1){}

    auto operator()(){
      auto pj = j;
      j = pj*rs;
      rs = 2*(i--)*rz-kyosu::rec(rs);
      return pj;
    }

    Z rz, rs, j, pj;
    int i;
  };

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y0>, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto egamma = eve::egamma(eve::as<u_t>());
    auto eps    = eve::eps(eve::as<u_t>());
    auto bd = bound(z);
    Z s{};
    mkjs jj(2*bd-2, z);
    auto sgn =  eve::sign_alternate(u_t(bd+1));
    for (int k = bd-1; k >= 1; --k)
    {
      auto sk = sgn*jj()/k;
      jj();
      sgn = -sgn;
      s+= sk;
    }
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), twoopi*((log(z/2)+egamma)*jj()-2*s));
  }
}
