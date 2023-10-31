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

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y1>, Z z) noexcept
  {
    std::cout << std::endl << "latte " << 1 << std::endl;
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto r1 = R(1, z);
    auto y0 = cyl_bessel_y0(z);
    std::cout << "ypred  " << y0 << std::endl;
    std::cout << "r      " << r1 << std::endl;
    auto recs1 = rec(r1)-twoopi/(z*cyl_bessel_j0(z)*y0);
    std::cout << "recs1  " << recs1 << std::endl;
    std::cout << "recs1*y0      " << recs1*y0 << std::endl;

    return y0*recs1;
  }
}
