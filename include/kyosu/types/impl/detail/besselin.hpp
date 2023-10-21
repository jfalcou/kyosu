//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/besseljn.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_in
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_in>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto miton = [](N n){
        if (n%4 == 0) return complex(eve::one(eve::as<e_t>()));
        else if (n%4 == 1) return  complex(eve::zero(eve::as<e_t>()), eve::mone(eve::as<e_t>()));
        else if (n%4 == 2) return complex(eve::mone(eve::as<e_t>()));
        else return complex(eve::zero(eve::as<e_t>()), eve::one(eve::as<e_t>()));
      };

      return miton(n)*cyl_bessel_jn(n,complex(-ipart(z), real(z)));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_in, n, z);
    }
  }
}
