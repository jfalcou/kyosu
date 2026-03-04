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

  //===-------------------------------------------------------------------------------------------
  //  cb_h12n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R>
  KYOSU_FORCEINLINE auto cb_h12n(N n, Z z, R& h1s, R& h2s) noexcept
  {
    auto an = eve::abs(n);
    an = eve::min(n, N(h1s.size()), N(h2s.size()));
    cb_jyn(n, z, h1s, h2s);
    for (int ii = 0; ii <= an; ++ii)
    {
      auto miyst = muli(h2s[ii]);
      h2s[ii] = h1s[ii] - miyst;
      h1s[ii] += miyst;
    }
    return kumi::tuple{h1s[n], h2s[n]};
  }

  template<int Kind, typename Z> KYOSU_FORCEINLINE auto cb_hn(int n, Z z) noexcept
  {
    auto j = cb_jn(n, z);
    auto y = cb_yn(n, z);
    if constexpr (Kind == 1) return j + muli(y);
    else return j - muli(y);
  }

  template<int Kind, typename Z, typename R> KYOSU_FORCEINLINE auto cb_hn(int n, Z z, R& hs) noexcept
  {
    std::size_t an = eve::abs(n);
    auto doit = [an, n, z, &hs](auto js, auto ys) {
      auto [jn, yn] = _::cb_jyn(n, z, js, ys);
      if constexpr (Kind == 1)
      {
        for (int ii = 0; ii < eve::min(size(hs), an + 1); ++ii) hs[ii] = js[ii] + muli + ys[ii];
        return jn + muli(yn);
      }
      else
      {
        for (int ii = 0; ii < eve::min(size(hs), an + 1); ++ii) hs[ii] = js[ii] + muli - ys[ii];
        return jn - muli(yn);
      }
    };
    return _::with_alloca<Z>(an + 1, doit);
  }
}
