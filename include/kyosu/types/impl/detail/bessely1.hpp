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
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto r1 = R(1, z);
//    std::cout << "r1 " << r1 << std::endl;
    auto y0 = cyl_bessel_y0(z);
//     std::cout << "y0 " << y0 << std::endl;
//     std::cout << "j0 " << cyl_bessel_j0(z) << std::endl;
    auto recs1 = rec(r1)-twoopi/(z*cyl_bessel_j0(z)*y0);
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), y0*recs1);
  }
}
