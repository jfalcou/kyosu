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
  auto dispatch(eve::tag_of<kyosu::exp> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto rho = eve::if_else(is_nan(rz), eve::allbits, eve::exp(rz));
      auto res = eve::if_else(is_real(z) || rz == eve::minf(eve::as(rz)),
                         C{rho, eve::zero(eve::as(rho))},
                         C{rho*c, rho*s});
      return if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), C{rz, eve::nan(eve::as(iz))}, res);
    }
    else
    {
      auto p = pure(z);
      auto az = abs(p);
      auto r  = exp(real(z));
      auto w = r*eve::sinc(az);
      return r*eve::cos(az) + w*p;
    }
  }


  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::expm1> const&, C const& z) noexcept
  -> C
  {
    if constexpr(kyosu::concepts::complex<C>)
    {
      auto [rz, iz] = z;
      auto sc = eve::sincos(iz);
      auto siz = get<0>(sc);
      auto ciz = get<1>(sc);
      auto cosm1 = [siz, ciz](auto b) {
        return eve::if_else(abs(ciz) < eve::pio_4(eve::as(b))
                           , eve::dec(ciz), -eve::sqr(siz)/(eve::inc(ciz)));
      };
      auto r = eve::fma(expm1(rz), ciz, cosm1(iz));
      auto i = eve::exp(rz)*siz;
      r = eve::if_else(rz == eve::inf(eve::as(rz)) && eve::is_not_finite(iz), rz, r);
      return  C{r, eve::if_else(kyosu::is_real(z), eve::zero, i)};
    }
    else
    {
      return dec(exp(z));
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::exp2> const&, C const& z) noexcept
  {
    using e_t = eve::underlying_type_t<C>;
    return exp(z*eve::log_2(eve::as<e_t>()));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::exp10> const&, C const& z) noexcept
  {
    using e_t = eve::underlying_type_t<C>;
    return exp(z*eve::log_10(eve::as<e_t>()));
  }

//   template<typename C>
//   KYOSU_FORCEINLINE constexpr
//   auto dispatch(eve::tag_of<kyosu::expmx2> const&, C const& z) noexcept
//   {
//     return exp(-sqr(z));
//   }

//   template<typename C>
//   KYOSU_FORCEINLINE constexpr
//   auto dispatch(eve::tag_of<kyosu::expx2> const&, C const& z) noexcept
//   {
//     return exp(sqr(z));
//   }

//   template<typename C>
//   KYOSU_FORCEINLINE constexpr
//   auto dispatch(eve::tag_of<kyosu::exp_i> const&, C const& z) noexcept
//   {
//     using u_t = eve::underlying_type_t<C>>;
//     auto ii = as_complex_t<u_t>(u_t(0), u_t(1));
//     return exp(ii*z);
//   }

//   template<typename C>
//   KYOSU_FORCEINLINE constexpr
//   auto dispatch(eve::tag_of<kyosu::exp_ipi> const&, C const& z) noexcept
//   {
//     if constexpr(complex<Z>)
//     {
//       using u_t = eve::underlying_type_t<C>>;
//       auto ii = as_complex_t<u_t>>(u_t(0), u_t(1));
//       auto [rz, iz] =ii*z;
//       auto [s, c]   = sinpicospi(iz);
//       auto rho = exp(rz*pi(as(rz)));
//       return if_else(is_real(z) || rz == minf(as(rz)),
//                      C{rho, zero(as(rho))},
//                      C{rho*c, rho*s});
//     }
//     else
//     {
//       using u_t = eve::underlying_type_t<C>>;
//       auto ipi = as_complex_t(u_t(0), eve::pi<as<u_t>());
//       return exp(ipi*z);
//     }
//   }

}
