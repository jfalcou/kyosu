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

namespace kyosu::_
{

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::cospi> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      iz *= eve::pi(as(iz));
      auto [s, c]   = eve::sinpicospi(rz);
      auto [sh, ch] = eve::sinhcosh(iz);
      auto r = c*ch;
      auto i = kyosu::if_else(is_imag(z) || kyosu::is_real(z),eve::zero, -s*sh);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        r = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::inf(as(r)), r);
        i = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::nan(as(r)), i);
        r = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, r);
        i = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, i);
      }
      return kyosu::to_complex(r, i);
    }
    else
    {
      using u_t = eve::underlying_type_t<C>;
      auto pi = eve::pi(eve::as<u_t>());
      auto p = kyosu::pure(z);
      auto az = kyosu::abs(p)*eve::pi(eve::as(kyosu::abs(p)));
      auto [s, c] = eve::sinpicospi(real(z));
      auto w = -s*eve::sinhc(az)*pi;
      return c*cosh(az)+w*pure(z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::secpi> const&, C const& z) noexcept
  {
    return kyosu::rec(kyosu::cospi(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sinpi> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto rz = -kyosu::imag(z);
      auto iz =  kyosu::real(z);
      rz *= eve::pi(as(rz));
      auto [s, c]   = eve::sinpicospi(iz);
      auto [sh, ch] = eve::sinhcosh(rz);
      auto r = c*sh;
      auto i = s*ch;
      if (any(kyosu::is_not_finite(z)))
      {
        r = eve::if_else(eve::is_infinite(rz) && eve::is_not_finite(iz), rz, r);
        i = eve::if_else(eve::is_infinite(rz) && eve::is_nan(iz), iz, i);
        r = eve::if_else(eve::is_nan(rz), rz, r);
        i = eve::if_else(eve::is_nan(rz), rz, i);
        i = eve::if_else(kyosu::is_imag(z), eve::zero, i);
        r = eve::if_else(kyosu::is_real(z), eve::zero, r);
      }
      return kyosu::to_complex(i, -r);
    }
    else
    {
      using u_t = eve::underlying_type_t<C>;
      auto pi = eve::pi(eve::as<u_t>());
      auto p = kyosu::pure(z);
      auto az = kyosu::abs(p)*pi;
      auto [s, c] = eve::sinpicospi(kyosu::real(z));
      auto w = c*eve::sinhc(az)*pi;
      return s*cosh(az)+w*p;
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::cscpi> const&, C const& z) noexcept
  {
    return kyosu::rec(kyosu::sinpi(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sinpicospi> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      iz *= eve::pi(as(iz));
      auto [s, c]   = eve::sinpicospi(rz);
      auto [sh, ch] = eve::sinhcosh(iz);
      auto rc = c*ch;
      auto ic = eve::if_else(kyosu::is_imag(z) || kyosu::is_real(z), eve::zero, -s*sh);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        rc = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::inf(eve::as(rc)), rc);
        ic = eve::if_else(eve::is_infinite(iz) && eve::is_not_finite(rz), eve::allbits, ic);
        rc = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, rc);
        ic = eve::if_else(eve::is_nan(iz) && eve::is_infinite(rz), eve::allbits, ic);
      }
      auto cpi = kyosu::to_complex(rc, ic);
      auto  arz = -kyosu::imag(z);
      auto  aiz =  kyosu::real(z);
      arz*= eve::pi(as(arz));
      auto [as, ac]   = eve::sinpicospi(aiz);
      auto [ash, ach] = eve::sinhcosh(arz);
      auto rs = ac*ash;
      auto is = as*ach;
      if (eve::any(kyosu::is_not_finite(z)))
      {
        rs = if_else(eve::is_infinite(aiz) && eve::is_not_finite(arz), arz, rs);
        is = if_else(eve::is_infinite(aiz) && eve::is_nan(arz), iz, is);
        rs = if_else(eve::is_nan(aiz), arz, rs);
        is = if_else(eve::is_nan(aiz), arz, is);
        is = if_else(eve::is_eqz(aiz), eve::zero, is);
        rs = if_else(eve::is_eqz(arz), eve::zero, rs);
      }
      auto spi = kyosu::to_complex(is, -rs);
      return kumi::tuple{spi, cpi};
    }
    else
    {
      using u_t = eve::underlying_type_t<C>;
      auto pi = eve::pi(eve::as<u_t>());
      auto p = kyosu::pure(z);
      auto az = kyosu::abs(p)*pi;
      auto [s, c] = eve::sinpicospi(kyosu::real(z));
      auto shc = eve::sinhc(az)*pi;
      auto ch  = eve::cosh(az);
      auto wc = c*shc;
      auto ws =-s*shc;
      auto sq = s*ch + wc*p;
      auto cq = c*ch + ws*p;
      return kumi::tuple{sq, cq};
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::tanpi> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto machin = [](auto z){
        auto [rz, iz] = z+z;
        auto [s, c] = eve::sinpicospi(iz);
        auto [sh, ch] = eve::sinhcosh(eve::pi(eve::as(rz))*rz);
        auto tmp = c+ch;
        auto rr = eve::if_else(kyosu::is_imag(z), eve::zero, sh/tmp);
        auto ii = eve::if_else(kyosu::is_real(z),eve:: zero, s/tmp);
        return kyosu::if_else(eve::is_infinite(rz), kyosu::to_complex(sign(rz)), kyosu::to_complex(rr, ii));
      };
      auto r = machin(kyosu::to_complex(-kyosu::imag(z), kyosu::real(z)));
      return kyosu::to_complex(kyosu::imag(r), -kyosu::real(r));
    }
    else
    {
      auto [s, c] = kyosu::sinpicospi(z);
      return s/c;
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::cotpi> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto r = kyosu::tanpi(z);
      r = kyosu::if_else(kyosu::is_infinite(r), C(), kyosu::rec(r));
      r = kyosu::if_else(kyosu::is_real(z) && eve::is_flint(kyosu::real(z)*2) && eve::is_not_flint(kyosu::real(z)), C{}, r);
      return  kyosu::if_else(kyosu::is_real(z), kyosu::to_complex(kyosu::real(r)), r);
    }
    else
    {
      auto [s, c] = kyosu::sinpicospi(z);
      return c/s;
    }
  }


}
