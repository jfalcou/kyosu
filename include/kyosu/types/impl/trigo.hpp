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
#include <kyosu/details/cayleyify.hpp>

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
      auto res = complex(r, i);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        res = eve::if_else(eve::is_infinite(rz) && eve::is_not_finite(iz), complex(eve::inf(eve::as(rz)), eve::nan(eve::as(rz))), res);
        res = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz),        complex(eve::nan(eve::as(rz)), eve::nan(eve::as(rz))), res);
      }
      return res;
    }
    else
    {
      return cayley_extend(cosh, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sech> const&, C const& z) noexcept
  {
    return kyosu::rec(kyosu::cosh(z));
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
      if (eve::all(kyosu::is_finite(z))) return complex(r, i);
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
      return complex(r, i);
    }
    else
    {
      return cayley_extend(sinh, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::csch> const&, C const& z) noexcept
  {
    return kyosu::rec(kyosu::sinh(z));
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
      auto ss = complex(rs, is);

      auto rc = c*ch;
      auto ic = s*sh;
      ic = eve::if_else(kyosu::is_eqz(kyosu::real(z)) || kyosu::is_real(z), eve::zero, ic);
      auto cc = complex(rc, ic);
      if (eve::any(kyosu::is_not_finite(z)))
      {
        cc = kyosu::if_else(infrz && is_not_finite(iz), complex(eve::inf(eve::as(rz)), eve::nan(eve::as(rz))), cc);
        cc = kyosu::if_else(nanrz && is_infinite(iz),   complex(eve::nan(eve::as(rz)), eve::nan(eve::as(rz))), cc);
      }
      return kumi::tuple{ss, cc};
    }
    else
    {
      return cayley_extend2(sinhcosh, z);
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
      return kyosu::if_else(eve::is_infinite(rz), kyosu::complex(eve::sign(rz)), kyosu::complex(rr, ii));
    }
    else
    {
      return cayley_extend(tanh, z);
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
      return cayley_extend(coth, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::cos> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      return cosh(complex(-kyosu::imag(z), kyosu::real(z)));
    }
    else
    {
      return cayley_extend(cos, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sec> const&, C const& z) noexcept
  {
    return kyosu::rec(kyosu::cos(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sin> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto s = kyosu::sinh(complex(-kyosu::imag(z), kyosu::real(z)));
      return complex(kyosu::imag(s), -kyosu::real(s));
    }
    else
    {
      return cayley_extend(sin, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::csc> const&, C const& z) noexcept
  {
    return kyosu::rec(kyosu::sin(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sincos> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [sh, ch] = sinhcosh(complex(-kyosu::imag(z), kyosu::real(z)));
      return kumi::tuple{complex(kyosu::imag(sh), -kyosu::real(sh)), ch};

    }
    else
    {
      return cayley_extend2(sincos, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::tan> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto t = kyosu::tanh(kyosu::complex(-kyosu::imag(z), kyosu::real(z)));
      return kyosu::complex(kyosu::imag(t), -kyosu::real(t));
    }
    else
    {
      return cayley_extend(tan, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::cot> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto r = kyosu::tan(z);
      return kyosu::if_else(kyosu::is_infinite(r), kyosu::complex(eve::zero(eve::as(eve::underlying_type_t<C>()))), kyosu::rec(r));
    }
    else
    {
      return cayley_extend(cot, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sinc> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto s = kyosu::sin(z);
      using u_t = eve::underlying_type_t<C>;
      return kyosu::if_else(kyosu::abs(z) < eve::eps(eve::as(u_t())), eve::one(eve::as(u_t())), s/z);
    }
    else
    {
      return cayley_extend(sinc, z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sinhc> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto s = kyosu::sinh(z);
      using u_t = eve::underlying_type_t<C>;
      return kyosu::if_else(kyosu::abs(z) < eve::eps(eve::as(u_t())), eve::one(eve::as(u_t())), s/z);
    }
    else
    {
      return cayley_extend(sinhc, z);
    }
  }

}
