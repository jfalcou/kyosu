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
      if(is_ltz(nu))
      {
        auto[s, c] = sinpicospi(z);
        return cyl_bessel_jnu(-nu, z)*s+cyl_bessel_ynu(-nu, z)*c;
      }
      else
      {
        return z+Z(nu);
      }
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_ynu, nu, z);
    }
  }

//   //===-------------------------------------------------------------------------------------------
//   //  sph_bessel_yn
//   //===-------------------------------------------------------------------------------------------
//   template<typename Z>
//   auto dispatch(eve::tag_of<kyosu::sph_bessel_yn>, int n, Z z) noexcept
//   {
//    if constexpr(concepts::complex<Z> )
//     {
//      using u_t = eve::underlying_type_t<Z>;
//       auto imzge0 = eve::is_gez(imag(z));
//       auto jn = sph_bessel_jn(n, z);
//       auto i = complex(u_t(0), u_t(1));
//       Z res;
//       if (eve::any(imzge0))
//       {
//         auto z1 = if_else(imzge0, z, conj(z));
//         res = jn-sph_bessel_h1n(n, z1);
//       }
//       if (!eve::all(imzge0))
//       {
//         auto z2 = if_else(imzge0, conj(z), z);
//         res = if_else(imzge0,  res, sph_bessel_h2n(n, z2)-jn);
//       }
//       return complex(-imag(res), real(res));
//     }
//     else
//     {
//       return cayley_extend_rev(sph_bessel_yn, n, z);
//     }
//   }


}
