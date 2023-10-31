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
  //  cyl_bessel_yn
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_yn>, int n, Z z) noexcept
  {
    std::cout << "icitte " << n << std::endl;
    if (n == 0) return cyl_bessel_y0(z);
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto rs = Rs(n, z);
    auto y1 = cyl_bessel_y1(z);
    auto ypred = y0;
    Z pr(one(eve::as<u_t>())); ;
    for(int i=n-1; i > 0; --i)
    {
      auto recsi = rec(rs[i-1])-twoopi/(cyl_bessel_jn(i-1, z)*ypred);
      pr *= recsi;
    }
    return pr;
  }
}
