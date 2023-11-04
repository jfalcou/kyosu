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
    auto j0z    = cyl_bessel_j0(z);
    auto bd = bound(z);
    auto js = Js(2*bd+1, z);
    Z s{}, sk{};
    auto sgn = u_t(1); //rec(j0z);
    for (int k = bd-1; k >= 1; --k)
    {
      sk = sgn*js[2*k]/k;
      std::cout << "k " << k << " -> " <<  sk << std::endl;
      sgn = -sgn;
      s+= sk;
    }
    s /= js[0];
//     int k = 1;
//     do {
//       sk = sgn*js[2*k]/k;
//       std::cout << "k " << k << " -> " <<  sk << std::endl;
//       ++k;
//       sgn = -sgn;
//       s+= sk;
//     } while (k < bd && eve::any(kyosu::abs(sk) > abs(s)*eps));
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), twoopi*((log(z/2)+egamma)-2*s)*js[0]); //cyl_bessel_j0(z));
  }
}
