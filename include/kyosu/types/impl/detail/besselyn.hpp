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
//    std::cout << std::endl << "icitte " << n << std::endl;
    auto y = cyl_bessel_y0(z);
    auto jold = cyl_bessel_j0(z);
    if (n == 0) return y;
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());

    for(int i=1; i <= n ; ++i)
    {
      auto jnew = cyl_bessel_jn(i, z);
      y = (jnew*y-twoopi*rec(z))/jold;
      jold = jnew;
    }
    return y;

//     auto rs = Rs(n, z);
//     auto ypred = y0;
//     std::cout  << "ypred  " << ypred << std::endl;
//     Z pr(eve::one(eve::as<u_t>())); ;
//     for(int i=n; i > 0; --i)
//     {
//       std::cout << "r      " << rs[i-1] << std::endl;
//       auto recsi = rec(rs[i-1])-twoopi/(z*cyl_bessel_jn(i-1, z)*ypred);
//       pr *= recsi;
//       ypred = pr*y0;
//       std::cout << "pr      " << pr << std::endl;

//     }
//     std::cout << "pr*y0      " << pr*y0 << std::endl;
//     return pr*y0;
  }
}
