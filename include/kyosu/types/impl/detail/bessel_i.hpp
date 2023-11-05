//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_i0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i0>, Z z) noexcept
  {
    return cyl_bessel_j0(complex(-ipart(z), real(z)));
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_i1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto [r, i] = cyl_bessel_j1(complex(-ipart(z), real(z)));
      return complex(i, -r);
    }
    else
    {
      return cayley_extend(cyl_bessel_i1, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_in
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_in>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_type_t<Z>;
      auto miton = [](N n){
        if (n%4 == 0) return complex(eve::one(eve::as<e_t>()));
        else if (n%4 == 1) return  complex(eve::zero(eve::as<e_t>()), eve::mone(eve::as<e_t>()));
        else if (n%4 == 2) return complex(eve::mone(eve::as<e_t>()));
        else return complex(eve::zero(eve::as<e_t>()), eve::one(eve::as<e_t>()));
      };
      auto an =  eve::abs(n);
      return miton(an)*cyl_bessel_jn(an,complex(-ipart(z), real(z)));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_in, n, z);
    }
  }  
}
