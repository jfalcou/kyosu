//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/besselj0.hpp>

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
    Z s{}, sk{};
    auto sgn = -rec(j0z);
    int k = 1;
    do {
      sk = sgn*cyl_bessel_jn(k+k, z)/k;
      ++k;
      sgn = -sgn;
      s+= sk;
    } while (eve::any(kyosu::abs(sk) > abs(s)*eps));
    return twoopi*((log(z/2)+egamma)-2*s)*cyl_bessel_j0(z);
  }
}
