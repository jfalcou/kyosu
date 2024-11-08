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
  // contains implementations of
  // cyl_bessel_h1
  // cyl_bessel_h2
  // cyl_bessel_h12
  /////////////////////////////////
  // utilities
  // cb_h12n
  /////////////////////////////////
  // implementation is done using j and y functions

  //===-------------------------------------------------------------------------------------------
  //  cb_h12
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, typename R1, typename R2> KYOSU_FORCEINLINE
  auto cb_h12(N n, Z z, R1 & h1s, R2 & h2s) noexcept
  {
    auto an =  int(eve::abs(n));
    EVE_ASSERT(int(size(h1s)) > an, "not enough room in h1s");
    EVE_ASSERT(int(size(h2s)) > an, "not enough room in h2s");
    cb_jy(n, z, h1s, h2s);
    for(int i=0; i <= an; ++i)
    {
      auto miyst = muli(h2s[i]);
      h2s[i] = h1s[i]-miyst;
      h1s[i] += miyst;
    }
    return kumi::tuple{h1s[n], h2s[n]};
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h1
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h1>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_bessel_j(n, z)+muli(cyl_bessel_y(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1n, n, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h2
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h2>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_bessel_j(n, z)-muli(cyl_bessel_y(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1, n, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h12
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R1,  typename R2>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h12>, N n, Z z, R1& h1s, R2& h2s) noexcept
  requires(concepts::complex<Z>)
  {
    return cb_h12(n, z, h1s, h2s);
  }
}
