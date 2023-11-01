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
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_kn>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      using u_t = eve::underlying_type_t<Z>;
      auto argz = arg(z);
      auto piotwo = eve::pio_2(eve::as<u_t>());
      auto i = complex(u_t(0), u_t(1));
      auto cpi = piotwo*i*exp_ipi(u_t(n)/2);
      auto cmi = -piotwo*i*exp_ipi(-u_t(n)/2);
      auto epio2 = exp_ipi(eve::half(eve::as<u_t>()));
      auto empio2 = exp_ipi(eve::mhalf(eve::as<u_t>()));
      auto r =  if_else(eve::is_ltz(argz)
                       , cpi*cyl_bessel_h1n(n, z*epio2)
                       , cmi*cyl_bessel_h2n(n, z*empio2));

      return r;
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_kn, n, z);
    }
  }
}
