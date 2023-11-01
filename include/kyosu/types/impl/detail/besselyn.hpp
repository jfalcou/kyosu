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
    using u_t   =  eve::underlying_type_t<Z>;
    auto y = cyl_bessel_y0(z);
    if (n != 0)
    {
      auto jold = cyl_bessel_j0(z);
      using u_t   =  eve::underlying_type_t<Z>;
      auto twoopi = eve::two_o_pi(eve::as<u_t>());

      for(int i=1; i <= n ; ++i)
      {
        auto jnew = cyl_bessel_jn(i, z);
        y = (jnew*y-twoopi*rec(z))/jold;
        jold = jnew;
      }
    }
    auto r = if_else(eve::is_gtz(real(z)) && is_real(z) && is_nan(y), complex(real(y)), y);
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), r);
  }
}
