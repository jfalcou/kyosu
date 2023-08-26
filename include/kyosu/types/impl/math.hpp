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
  auto dispatch(eve::tag_of<kyosu::exp> const&, C const& z) noexcept
  {
    if constexpr(concepts::complex<C> )
    {
      auto [rz, iz] = z;
      auto [s, c]   = eve::sincos(iz);
      auto rho = eve::if_else(is_nan(rz), eve::allbits, eve::exp(rz));
      auto res = eve::if_else(is_real(z) || rz == eve::minf(eve::as(rz)),
                              to_complex(rho, eve::zero(eve::as(rho))),
                              to_complex(rho*c, rho*s));
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
      return  to_complex(r, eve::if_else(kyosu::is_real(z), eve::zero, i));
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
    return kyosu::exp(z*eve::log_10(eve::as<e_t>()));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::expmx2> const&, C const& z) noexcept
  {
    return kyosu::exp(-sqr(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::expx2> const&, C const& z) noexcept
  {
    return exp(sqr(z));
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::exp_i> const&, C const& z) noexcept
 {
   using c_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
   const auto ii =  c_t(0, 1);
   return kyosu::exp(ii*z);
 }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::exp_ipi> const&, C const& z) noexcept
  {
    using c_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
    if constexpr(kyosu::concepts::complex<C>)
    {
      const auto ii =  c_t(0, 1);
      auto [rz, iz] =ii*z;
      auto [s, c]   = eve::sinpicospi(iz);
      auto rho = eve::exp(rz*eve::pi(eve::as(rz)));
      return eve::if_else(kyosu::is_real(z) || rz == eve::minf(eve::as(rz)),
                          kyosu::to_complex(rho, eve::zero(eve::as(rho))),
                          kyosu::to_complex(rho*c, rho*s)
                         );
    }
    else
    {
      using u_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
      const auto ipi = c_t(u_t(0), eve::pi<eve::as<u_t>());
      return kyosu::exp(ipi*z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::log> const&, C const& z) noexcept
  {
    using c_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
    if constexpr(kyosu::concepts::complex<C>)
    {
      auto arg = [](auto z){ return eve::pedantic(eve::atan2)(kyosu::imag(z), kyosu::real(z));};
      auto [rz, iz] = z;
      auto infty = eve::inf(eve::as(rz));
      auto argz = arg(z);
      auto absz = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz), infty, kyosu::abs(z));
      auto la = eve::log(absz);
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), to_complex(la, eve::zero(eve::as(rz))), to_complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), to_complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      auto az = kyosu::abs(z);
      auto v = kyosu::pure(z);
      auto s = kyosu::real(z);
      auto z1 = (eve::acos(s/az)/abs(v))*v+eve::log(az);
//       auto tmp =  kyosu::if_else( kyosu::is_real(z)
//                                 ,  kyosu::log(kyosu::real(z))
//                                 , z1
//                                 );
//       return tmp;

//       return kyosu::if_else( kyosu::is_eqz(z)
//                            , eve::minf(eve::as(az))
//                            , tmp
//                            );

      return kyosu::if_else( kyosu::is_eqz(z)
                           , eve::minf(eve::as(az))
                           , z1
                           );
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::log10> const&, C const& z) noexcept
  {
    using c_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
    if constexpr(kyosu::concepts::complex<C>)
    {
      auto [rz, iz] = z;
      auto infty = eve::inf(eve::as(rz));
      auto arg = [](auto z){ return eve::pedantic(eve::atan2)(kyosu::imag(z), kyosu::real(z));};
      auto argz = arg(z)*eve::invlog_10(eve::as(rz));
      auto absz = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz), infty, kyosu::abs(z));
      auto la = eve::log10(absz);
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), to_complex(la, eve::zero(eve::as(rz))), to_complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), to_complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      using e_t = eve::underlying_type_t<C>;
      return log(z)*eve::invlog_10(eve::as<e_t>());
     }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::log2> const&, C const& z) noexcept
  {
    using c_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
    if constexpr(kyosu::concepts::complex<C>)
    {
      auto [rz, iz] = z;
      auto infty = eve::inf(eve::as(rz));
      auto arg = [](auto z){ return eve::pedantic(eve::atan2)(kyosu::imag(z), kyosu::real(z));};
      auto argz = arg(z)*eve::invlog_2(eve::as(rz));
      auto absz = eve::if_else(eve::is_nan(rz) && eve::is_infinite(iz), infty, kyosu::abs(z));
      auto la = eve::log2(absz);
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), to_complex(la, eve::zero(eve::as(rz))), to_complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), to_complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      using e_t = eve::underlying_type_t<C>;
      return log(z)*eve::invlog_2(eve::as<e_t>());
     }
  }

}
