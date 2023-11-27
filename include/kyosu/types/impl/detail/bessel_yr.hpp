//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_jyr.hpp>
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_ynu
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_ynu>, N  nu, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto doit = [nu, z](auto js, auto ys){
        auto [j, y] = cb_jyr(eve::abs(nu), z, js, ys);
        return kumi::tuple{j, y};
      };
      auto [j, y] = with_alloca<Z>(int(nu)+1, doit);

      if(eve::is_ltz(nu))
      {
        if (eve::is_flint(nu))
        {
          return cyl_bessel_yn(int(nu), z);
        }
        else
        {
          auto [s, c] = sinpicospi(z);
          return j*s+y*c;
        }
      }
      else
      {
        if (eve::is_flint(nu))
        {
          return cyl_bessel_yn(int(nu), z);
        }
        else
        {
          return y;
        }
      }
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_ynu, nu, z);
    }
  }
}
