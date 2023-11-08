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
      auto muli = [](auto z){ auto [r, i] = z; return complex(-i, r); };
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
      auto muli = [](auto z){ auto [r, i] = z; return complex(-i, r); };
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
      }
      else
      {
        auto imzge0 = eve::is_gez(imag(z));
        using u_t   =  eve::underlying_type_t<Z>;
        auto i = complex(u_t(0), u_t(1));
        auto rz = rec(z);
        auto iz = complex(-ipart(z), real(z));
        auto h0 = -i*exp(iz)/z;
        if(n == 0) return h0;
        auto h1 = (rz-i)*h0;
        if(n == 1) return h1;

        auto br_imzge0 = [&h0, &h1, rz, n](){
          auto h2 = h1;
          for(int i=1; i < n; ++i)
          {
            auto f = (2*i+1)*rz;
            h2 = f*h1-h0;
            h0 = h1;
            h1 = h2;
          }
          return h2;
        };

        auto br_imzlt0 = [n, z](){
          return 2*sph_bessel_jn(n, z)-sph_bessel_h2n(n, z);
        };

        auto res = br_imzge0();
        if (eve::all(imzge0)) return res;
        auto res1 = br_imzlt0();
        return if_else(imzge0, res, res1);
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
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h2n>, int n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z>)
    {
      if (n < 0)
      {
      }
      else
      {
        auto imzlt0 = eve::is_ltz(imag(z));
        using u_t   =  eve::underlying_type_t<Z>;
        auto i = complex(u_t(0), u_t(1));
        auto rz = rec(z);
        auto miz = complex(ipart(z), -real(z));
        auto h0 = i*exp(miz)/z;
        if(n == 0) return h0;
        auto h1 = (rz+i)*h0;
        if(n == 1) return h1;

        auto br_imzlt0 = [&h0, &h1, rz, n](){
          auto h2 = h1;
          for(int i=1; i < n; ++i)
          {
            auto f = (2*i+1)*rz;
            h2 = f*h1-h0;
            h0 = h1;
            h1 = h2;
          }
          return h2;
        };

        auto br_imzge0 = [n, z](){
          return 2*sph_bessel_jn(n, z)+sph_bessel_h1n(n, z);
        };

        auto res = br_imzlt0();
        if (eve::all(imzlt0)) return res;
        auto res1 = br_imzge0();
        return if_else(imzlt0, res, res1);
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
    return sph_bessel_h1n(0, z);
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_h2_1>, Z z) noexcept
  {
    return sph_bessel_h2n(1, z);
  }


}
