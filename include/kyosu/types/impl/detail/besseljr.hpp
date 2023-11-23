//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jnu
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jnu>, N nn, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      if(is_ltz(nu))
      {
        auto[s, c] = sinpicospi(z);
        return cyl_bessel_jnu(-nu, z)*s-cyl_bessel_ynu(-nu, z)*c;
      }
      else
      {
        return z+Z(nn);
      }
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_jnu, nn, z);
    }
  }

//   //===-------------------------------------------------------------------------------------------
//   //  sph_bessel_jnu
//   //===-------------------------------------------------------------------------------------------

//   template<eve::floating_scalar_value N, typename Z>
//   auto dispatch(eve::tag_of<kyosu::sph_bessel_jnu>, N n, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       using u_t = eve::underlying_type_t<Z>;
//       auto bd = [z](int n){
//         auto st = eve::abs(eve::sin(eve::abs(arg(z))));
//         auto r  = kyosu::abs(z);
//         auto m = eve::maximum(eve::ceil((u_t(1.83)+u_t(4.1)*eve::pow(st, u_t(0.33)))*
//                                         eve::pow(r, (u_t(0.91)-u_t(0.43)*eve::pow(st, u_t(0.36))))+9*(1-eve::sqrt(st))));
//         auto nn = (eve::any(is_real(z))) ? n+5 : n;
//         return eve::max(nn, int(inc(m)));
//       };

//       auto j0 = kyosu::sph_bessel_j0(z);
//       if (n == 0) return j0;
//       auto j1 = kyosu::sph_bessel_j1(z);
//       if (n == 1) return j1;

//       auto rz = kyosu::rec(z);
//       auto nn = bd(n);
//       Z jnuext(kyosu::complex(u_t(0)));
//       Z j(kyosu::complex(eve::sqrtsmallestposval(eve::as<u_t>())));
//       auto init = j;
//       auto jcur = jnuext;
//       auto res = j;
//       for(int i=nn-1; i > 0 ; --i)
//       {
//         jcur = (2*i+1)*rz*j-jnuext;
//         if(i == n) res = j;
//         jnuext = j;
//         j = jcur;
//       }
//       auto j0ltj1 = kyosu::abs(j0) <= kyosu::abs(j1);
//       auto scalej0 = (j0/jcur);
//       auto scalej1 = (j1/jnuext);
//       res *= if_else(j0ltj1, scalej0, scalej1);
//       return if_else(is_eqz(z), eve::zero, res);
//     }
//     else
//     {
//       return cayley_extend_rev(sph_bessel_jn, n, z);
//     }
//   }

}
