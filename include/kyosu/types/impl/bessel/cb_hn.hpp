//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{
  /////////////////////////////////
  // contains implementations of
  // cyl_bessel_h1_0
  // cyl_bessel_h1_1
  // cyl_bessel_h1n
  // cyl_bessel_h2_0
  // cyl_bessel_h2_1
  // cyl_bessel_h2n
  // cyl_bessel_h12n
  /////////////////////////////////
  // utilities
  // cb_h12n
  /////////////////////////////////
  // implementation is done from j and y functions

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h1_0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h1_0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cyl_bessel_j0(z)+muli(cyl_bessel_y0(z));
    }
    else
    {
      return cayley_extend(cyl_bessel_h1_0, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h2_0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h2_0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cyl_bessel_j0(z)-muli(cyl_bessel_y0(z));
    }
    else
    {
      return cayley_extend(cyl_bessel_h2_0, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h1_1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h1_1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cyl_bessel_j1(z)+muli(cyl_bessel_y1(z));
    }
    else
    {
      return cayley_extend(cyl_bessel_h1_1, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h2_1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h2_1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      return  cyl_bessel_j1(z)-muli(cyl_bessel_y1(z));
    }
    else
    {
      return cayley_extend(cyl_bessel_h2_1, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_h12n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto cb_h12n(N n, Z z, R & h1s, R& h2s) noexcept
  {
    for(int i=0; i <= eve::abs(n+1); ++i)
    {
      auto miyst = muli(h2s[i]);
      h2s[i] = h1s[i]-miyst;
      h1s[i] += miyst;
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h1n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h1n>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_bessel_jn(n, z)+muli(cyl_bessel_yn(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1n, n, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_h2n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_h2n>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cyl_bessel_jn(n, z)-muli(cyl_bessel_yn(n, z));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_h1n, n, z);
    }
  }

//   //===-------------------------------------------------------------------------------------------
//   //  cyl_bessel_h12n
//   //===-------------------------------------------------------------------------------------------
//   template<eve::integral_scalar_value N, kyosu::concepts::complex Z, typename R>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_h12n>, N n, Z z, R& h1s, R& h2s) noexcept
//   requires(concepts::complex<Z>)
//   {
//     return cb_h12n(n, z, js, ys);
//   }
}
