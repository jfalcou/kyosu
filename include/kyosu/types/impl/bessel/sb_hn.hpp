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

  /////////////////////////////////
  // utilities
  // sb_h1n
  // sb_h2n
  // sb_hn
  ////////////////////////////////

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  spherical bessel of the third kind
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  template<eve::integral_scalar_value N, typename Z>
  auto sb_h2n(N n, Z z) noexcept
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

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_h1n(N n, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    return eve::sign_alternate(u_t(n))*sb_h2n(n, -z);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_h1n(int n, Z z) noexcept
  {
    using u_t   =  eve::underlying_type_t<Z>;
    return eve::sign_alternate(u_t(n))*sb_h2n(n, -z);
  }

  template<int Kind, eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_hn(N n, Z z) noexcept
  {
    if constexpr(Kind == 1)
      return sb_h1n(n, z);
    else
      return sb_h2n(n, z);
  }
}
