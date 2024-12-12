//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/with_alloca.hpp>
#include <kyosu/types/impl/besselr/cb_jyr.hpp>
namespace kyosu::_
{
  /////////////////////////////////
  // needed by the implementations of
  // cyl_bessel_h1
  // cyl_bessel_h2
  // cyl_bessel_h12
  /////////////////////////////////
  // utilities
  // cb_h12r
  // cb_h1r
  // cb_h2r
  /////////////////////////////////
  // implementation is done using j and y functions

  //===-------------------------------------------------------------------------------------------
  //  cb_h12r
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, typename R1, typename R2> KYOSU_FORCEINLINE
  auto cb_h12r(N n, Z z, R1 & h1s, R2 & h2s) noexcept
  {
    auto an =  int(eve::abs(n));
    EVE_ASSERT(int(size(h1s)) > an, "not enough room in h1s");
    EVE_ASSERT(int(size(h2s)) > an, "not enough room in h2s");
    cb_jyr(n, z, h1s, h2s);
    for(int i=0; i <= an; ++i)
    {
      auto miyst = muli(h2s[i]);
      h2s[i] = h1s[i]-miyst;
      h1s[i] += miyst;
    }
    return kumi::tuple{h1s[n], h2s[n]};
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_h1r
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_h1r(N v, Z z) noexcept
  {
    return cb_jr(v, z)+muli(cb_yr(v, z));
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_h2r
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_h2r(N v, Z z) noexcept
  {
     return cb_jr(v, z)-muli(cb_yr(v, z));
  }

  ///////////////////////////////////////////////////////////////
  //new
  ///////////////////////////////////////////////////////////////


  //===-------------------------------------------------------------------------------------------
  //  cb_hr
  //===-------------------------------------------------------------------------------------------
  template<int Kind, eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_hr(N v, Z z) noexcept
  {
    if constexpr(Kind ==  1)
      return cb_jr(v, z)+muli(cb_yr(v, z));
    else
      return cb_jr(v, z)-muli(cb_yr(v, z));
  }

  template<int Kind, eve::floating_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto cb_hr(N v, Z z, R& hs) noexcept
  {
    auto an =  std::size_t(eve::abs(v));
    auto doit = [an, v, z, &hs](auto js, auto ys){
      auto [jv, yv] = _::cb_jyr(v, z, js, ys);
      if constexpr(Kind == 1)
      {
        for(int i = 0; i < eve::min(size(hs), an+1); ++i) hs[i] = js[i]+muli(ys[i]);
        return jv+muli(yv);
      }
      else
      {
        for(int i = 0; i < eve::min(size(hs), an+1); ++i) hs[i] = js[i]-muli(ys[i]);
        return jv-muli(yv);
      }
    };
    return _::with_alloca<Z>(an+1, doit);
  }
}
