//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{
  /////////////////////////////////
  // utilities
  // cb_h12n
  // cb_h1_0
  // cb_h2_0
  // cb_h1_1
  // cb_h2_1
  // cb_h1n
  // cb_h2n
  /////////////////////////////////
  // implementation is done using j and y functions

//   template<typename Z> KYOSU_FORCEINLINE
//   auto cb_h1_0(Z z) noexcept
//   {
//     return  cb_j0(z)+muli(cb_y0(z));
//   }

//   template<typename Z> KYOSU_FORCEINLINE
//   auto cb_h2_0(Z z) noexcept
//   {
//     return cb_j0(z)-muli(cb_y0(z));
//   }

//   template<typename Z> KYOSU_FORCEINLINE
//   auto cb_h1_1(Z z) noexcept
//   {
//     return   cb_j1(z)+muli(cb_y1(z));
//   }

//   template<typename Z> KYOSU_FORCEINLINE
//   auto cb_h2_1(Z z) noexcept
//   {
//     return  cb_j1(z)-muli(cb_y1(z));
//   }


//   template<typename Z> KYOSU_FORCEINLINE
//   auto cb_h2n(int n, Z z) noexcept
//   {
// //    auto [j, y] = cyl_bessel_jyn(n, z);
//     auto  j = cyl_bessel_jn(n, z);
//     auto  y = cyl_bessel_yn(n, z);
//     return j-muli(y);
//   }

  //===-------------------------------------------------------------------------------------------
  //  cb_h12n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto cb_h12n(N n, Z z, R & h1s, R& h2s) noexcept
  {
    auto an = eve::abs(n);
    an = eve::min(n, N(h1s.size()), N(h2s.size()));
    cb_jyn(n, z, h1s, h2s);
    for(int i=0; i <= an; ++i)
    {
      auto miyst = muli(h2s[i]);
      h2s[i] = h1s[i]-miyst;
      h1s[i] += miyst;
    }
    return kumi::tuple{h1s[n], h2s[n]};
  }

  ///////////////////////////////////////////////////////////////
  //new
  ///////////////////////////////////////////////////////////////

  template<int Kind, typename Z> KYOSU_FORCEINLINE
  auto cb_hn(int n, Z z) noexcept
  {
    auto  j = cb_jn(n, z);
    auto  y = cb_yn(n, z);
    if constexpr(Kind == 1)
      return j+muli(y);
    else
      return j-muli(y);
  }

  template<int Kind, typename Z, typename R> KYOSU_FORCEINLINE
  auto cb_hn(int n, Z z, R& hs) noexcept
  {
    std::size_t an = eve::abs(n);
    auto doit = [an, n, z, &hs](auto js, auto ys){
      auto [jn, yn] = _::cb_jyn(n, z, js, ys);
      if constexpr(Kind == 1)
      {
        for(int i = 0; i < eve::min(size(hs), an+1); ++i) hs[i] = js[i]+muli+ys[i];
        return jn+muli(yn);
      }
      else{
        for(int i = 0; i < eve::min(size(hs), an+1); ++i) hs[i] = js[i]+muli-ys[i];
        return jn-muli(yn);
      }
    };
    return _::with_alloca<Z>(an+1, doit);
  }
}
