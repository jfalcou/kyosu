//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <iostream>

namespace kyosu::_
{
  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::cosh> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto r = c*ch;
      auto i = s*sh;
      i = eve::if_else(kyosu::is_eqz(kyosu::ipart(z)) || kyosu::is_real(z), eve::zero, i);
      auto res = to_complex(r, i);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        res = eve::if_else(eve::is_infinite(rz) && eve::is_not_finite(iz), to_complex(eve::inf(eve::as(rz)), eve::nan(eve::as(rz))), res);
        res = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz),        to_complex(eve::nan(eve::as(rz)), eve::nan(eve::as(rz))), res);
      }
      return res;
    }
    else
    {
      auto e = kyosu::exp(z);
      return eve::average(e, rec(e));
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sinh> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto r = c*sh;
      auto i = s*ch;
      if (eve::all(kyosu::is_finite(z))) return to_complex(r, i);
      auto infrz = kyosu::is_infinite(rz);
      auto nanrz = kyosu::is_nan(rz);
      if (eve::any(infrz || nanrz))
      {
        r = eve::if_else(infrz && eve::is_not_finite(iz), rz, r);
        i = eve::if_else(infrz && eve::is_nan(iz), eve::allbits, i);
        r = eve::if_else(nanrz, eve::allbits, r);
        i = eve::if_else(nanrz, eve::allbits, i);
      }
      i = eve::if_else(kyosu::is_real(z), eve::zero, i);
      r = eve::if_else(kyosu::is_eqz(kyosu::real(z)), eve::zero, r);
      return to_complex(r, i);
    }
    else
    {
      auto e = kyosu::exp(z);
      return eve::average(e, -kyosu::rec(e));
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sinhcosh> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto rs = c*sh;
      auto is = s*ch;
      auto infrz = eve::is_infinite(rz);
      auto nanrz = eve::is_nan(rz);
      if (eve::any(infrz || nanrz))
      {
        rs = eve::if_else(infrz && eve::is_not_finite(iz), rz, rs);
        is = eve::if_else(infrz && eve::is_nan(iz), eve::allbits, is);
        rs = eve::if_else(nanrz, eve::allbits, rs);
        is = eve::if_else(nanrz, eve::allbits, is);
      }
      is = eve::if_else(kyosu::is_real(z), eve::zero, is);
      rs = eve::if_else(kyosu::is_eqz(kyosu::real(z)), eve::zero, rs);
      auto ss = to_complex(rs, is);

      auto rc = c*ch;
      auto ic = s*sh;
      ic = eve::if_else(kyosu::is_eqz(kyosu::real(z)) || kyosu::is_real(z), eve::zero, ic);
      auto cc = to_complex(rc, ic);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        cc = kyosu::if_else(infrz && is_not_finite(iz), to_complex(eve::inf(eve::as(rz)), eve::nan(eve::as(rz))), cc);
        cc = kyosu::if_else(nanrz && is_infinite(iz),   to_complex(eve::nan(eve::as(rz)), eve::nan(eve::as(rz))), cc);
      }
      return kumi::tuple{ss, cc};
    }
    else
    {
      auto e = kyosu::exp(z);
      auto ie = kyosu::rec(e);
      return kumi::tuple{ eve::average(e, -ie),  eve::average(e, ie)};
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::tanh> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto zz = z+z;
      auto [rz, iz] = zz;
      auto [s, c] = eve::sincos(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto tmp = c+ch;
      auto rr = eve::if_else(eve::is_eqz(kyosu::real(z)), eve::zero, sh/tmp);
      auto ii = eve::if_else(kyosu::is_real(z), eve::zero, s/tmp);
      return kyosu::if_else(eve::is_infinite(rz), kyosu::to_complex(eve::sign(rz)), kyosu::to_complex(rr, ii));
    }
    else
    {
      auto e = kyosu::expm1(z+z);
      return e/(e+2);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::coth> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      return kyosu::rec(kyosu::tanh(z));
    }
    else
    {
      auto e = kyosu::expm1(z+z);
      return (e+2)/e;
    }
  }

}
