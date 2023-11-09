//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_j.hpp>
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  utilities
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  template < typename Z> struct mkjs
  {
    mkjs(size_t n, Z z):
      rz(kyosu::rec(z)),
      rs(kyosu::_:: R(n, z)),
      j(kyosu::cyl_bessel_jn(n, z)),
      i(n-1){}

    auto operator()(){
      auto pj = j;
      j = pj*rs;
      rs = 2*(i--)*rz-kyosu::rec(rs);
      return pj;
    }

    Z rz, rs, j, pj;
    int i;
  };

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  cylindrical bessel
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y0>, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto egamma = eve::egamma(eve::as<u_t>());
    auto eps    = eve::eps(eve::as<u_t>());
    auto bd = bound(z);
    Z s{};
    mkjs jj(2*bd-2, z);
    auto sgn =  eve::sign_alternate(u_t(bd+1));
    for (int k = bd-1; k >= 1; --k)
    {
      auto sk = sgn*jj()/k;
      jj();
      sgn = -sgn;
      s+= sk;
    }
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), twoopi*((log(z/2)+egamma)*jj()-2*s));
  }


  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_y1>, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto twoopi = eve::two_o_pi(eve::as<u_t>());
    auto r1 = R(1, z);
    auto y0 = cyl_bessel_y0(z);
    auto recs1 = rec(r1)-twoopi/(z*cyl_bessel_j0(z)*y0);
    return if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), y0*recs1);
  }


  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_yn
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_yn>, int nn, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    auto y = cyl_bessel_y0(z);
    if (nn != 0)
    {
      int n = eve::abs(nn);
      auto do_it =  [n, z, &y](auto js){
        mkjs jj(n, z);
        for(int i=n; i >= 0 ; --i)  js[i] = jj();
        using u_t   =  eve::underlying_type_t<Z>;
        auto twoopi = eve::two_o_pi(eve::as<u_t>());
        auto b = twoopi*rec(z);
        for(int i=1; i <= n ; ++i) y = fms(js[i], y, b)/js[i-1];
      };
      kyosu::_::with_alloca<Z>(n+1, do_it);
      auto r = if_else(eve::is_gtz(real(z)) && is_real(z) && is_nan(y), complex(real(y)), y);
      r = if_else(is_eqz(z), complex(eve::minf(eve::as<u_t>())), r);
      return nn < 0 ? r*eve::sign_alternate(u_t(n)) : r;
    }
    else return y;
  }

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  spherical bessel
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  //===-------------------------------------------------------------------------------------------
  //  sph_bessel_y0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_y0>, Z z) noexcept
  {
    return -cos(z)/z;
  }

  //===-------------------------------------------------------------------------------------------
  //  sph_bessel_y1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_y1>, Z z) noexcept
  {
    return -cos(z)/sqr(z)-sinc(z);
  }


  //===-------------------------------------------------------------------------------------------
  //  sph_bessel_yn
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_yn>, int n, Z z) noexcept
  {
   if constexpr(concepts::complex<Z> )
    {
     using u_t = eve::underlying_type_t<Z>;
      auto imzge0 = eve::is_gez(imag(z));
      auto jn = sph_bessel_jn(n, z);
      auto i = complex(u_t(0), u_t(1));
      Z res;
      if (eve::any(imzge0))
      {
        auto z1 = if_else(imzge0, z, conj(z));
        res = jn-sph_bessel_h1n(n, z1);
      }
      if (!eve::all(imzge0))
      {
        auto z2 = if_else(imzge0, conj(z), z);
        res = if_else(imzge0,  res, sph_bessel_h2n(n, z2)-jn);
      }
      return complex(-imag(res), real(res));
    }
    else
    {
      return cayley_extend_rev(sph_bessel_yn, n, z);
    }
  }


}