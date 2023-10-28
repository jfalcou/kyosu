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
  auto dispatch(eve::tag_of<kyosu::cyl_lbessel_in>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto logmiton = [](N n){
        auto nmod4 = n%4;
        if (nmod4 == 0) return complex(eve::zero(eve::as<e_t>()));
        else if (nmod4 == 1) return  complex(eve::zero(eve::as<e_t>()), -eve::pio_2(eve::as<e_t>()));
        else if (nmod4 == 2) return complex(eve::zero(eve::as<e_t>()), eve::pi(eve::as<e_t>()));
        else return complex(eve::zero(eve::as<e_t>()), eve::pio_2(eve::as<e_t>()));
      };

      return arg_adjust(logmiton(n)+cyl_lbessel_jn(n,complex(-ipart(z), real(z))));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_in, n, z);
    }
  }
}
