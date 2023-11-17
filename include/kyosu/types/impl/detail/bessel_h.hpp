//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_j.hpp>
#include <kyosu/types/impl/detail/bessel_y.hpp>
#include <vector>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  cylindrical bessel of the third kind
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h1n
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h1n>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cyl_bessel_jn(n, z)+muli(cyl_bessel_yn(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1n, n, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h2n>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cyl_bessel_jn(n, z)-muli(cyl_bessel_yn(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h2n, n, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  spherical bessel of the third kind
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------


  //===-------------------------------------------------------------------------------------------
  //  sph_bessel_h1n
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h1n>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      if (n < 0)
      {
        return eve::nan(as(z));
      }
      else
      {
        using u_t   =  eve::underlying_type_t<Z>;
        return eve::sign_alternate(u_t(n))*sph_bessel_h2n(n, -z);
      }
    }
    else
    {
      return cayley_extend_rev(sph_bessel_h1n, n, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h1_0>, Z z) noexcept
  {
    return sph_bessel_h1n(0, z);
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h1_1>, Z z) noexcept
  {
    return sph_bessel_h1n(1, z);
  }

  //===-------------------------------------------------------------------------------------------
  //  sph_bessel_h2n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h2n>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      if (n < 0)
      {
        return eve::nan(as(z));
      }
      else
      {
        auto imzlt0 = eve::is_ltz(imag(z));
        z = if_else(imzlt0, z, -z);
        using u_t   =  eve::underlying_type_t<Z>;
        auto i = complex(u_t(0), u_t(1));
        auto rz = rec(z);
        auto miz = mulmi(z);
        auto h0 = if_else(imzlt0, i*exp(miz), -i*exp(-miz))*rz;
        if(n == 0) return h0;
        auto h1 = if_else(imzlt0, (rz+i),(rz-i))*h0 ;
        if(n == 1) return if_else(imzlt0,h1, -h1);

        auto h2 = h1;
        for(int i=1; i < n; ++i)
        {
          auto f = (2*i+1)*rz;
          h2 = f*h1-h0;
          h0 = h1;
          h1 = h2;
        }
        return if_else(imzlt0, h2, eve::sign_alternate(u_t(n))*h2);
      }
    }
    else
    {
      return cayley_extend_rev(sph_bessel_h2n, n, z);
    }
  }


  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h2_0>, Z z) noexcept
  {
    return sph_bessel_h2n(0, z);
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h2_1>, Z z) noexcept
  {
    return sph_bessel_h2n(1, z);
  }


}
