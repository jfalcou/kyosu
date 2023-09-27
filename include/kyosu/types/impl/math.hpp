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
#include <kyosu/types/impl/reals.hpp>
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
                              complex(rho, eve::zero(eve::as(rho))),
                              complex(rho*c, rho*s));
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
      return  complex(r, eve::if_else(kyosu::is_real(z), eve::zero, i));
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
                          kyosu::complex(rho, eve::zero(eve::as(rho))),
                          kyosu::complex(rho*c, rho*s)
                         );
    }
    else
    {
      using u_t = eve::underlying_type_t<C>;
      const auto ipi = complex(u_t(0), eve::pi(eve::as<u_t>()));
      return kyosu::exp(ipi*z);
    }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::log_abs> const&, C const& z) noexcept
  {
    using u_t = eve::underlying_type_t<C>;
    return eve::half(eve::as<u_t>())*eve::log(kyosu::sqr_abs(z));
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
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), complex(la, eve::zero(eve::as(rz))), complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      auto az = kyosu::abs(z);
      auto v = kyosu::pure(z);
      auto s = kyosu::real(z);
      auto z1 = (eve::acos(s/az)/abs(v))*v+eve::log(az);
      auto tmp =  kyosu::if_else( kyosu::is_real(z)
                                ,  kyosu::log(kyosu::real(z))
                                , z1
                                );
      return kyosu::if_else( kyosu::is_eqz(z)
                           , eve::minf(eve::as(az))
                           , tmp
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
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), complex(la, eve::zero(eve::as(rz))), complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), complex(infty, iz), r);
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
      auto r = kyosu::if_else(kyosu::is_real(z) && eve::is_positive(rz), complex(la, eve::zero(eve::as(rz))), complex(la, argz));
      if(eve::any(kyosu::is_not_finite(z)))
      {
        r = kyosu::if_else(eve::is_infinite(rz) && eve::is_nan(iz), complex(infty, iz), r);
      }
      return r;
    }
    else
    {
      using e_t = eve::underlying_type_t<C>;
      return log(z)*eve::invlog_2(eve::as<e_t>());
     }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::log1p> const&, C const& z) noexcept
  {
    using c_t = as_cayley_dickson_n_t<2,eve::underlying_type_t<C>>;
      using e_t = eve::underlying_type_t<C>;
    if constexpr(kyosu::concepts::complex<C>)
    {
      auto m = kyosu::inc(z);
      auto arg = [](auto z){ return eve::pedantic(eve::atan2)(kyosu::imag(z), kyosu::real(z));};
      auto theta = eve::if_else((kyosu::is_real(m) && eve::is_nltz(kyosu::real(m))), eve::zero, arg(m)) ;
      auto rz =  kyosu::real(z);
      auto iz2 =  eve::sqr(kyosu::imag(z));
      return complex(eve::half(eve::as<e_t>())*eve::log1p(rz*(rz+e_t(2))+iz2), theta);
    }
    else
    {
      auto incz = inc(z);
      auto az = kyosu::abs(incz);
      auto az2 = kyosu::sqr_abs(z) + 2*real(z);
      auto v = kyosu::pure(z);
      auto s = kyosu::real(incz);
      auto z1 = (eve::acos(s/az)/abs(v))*v+ eve::half(eve::as<e_t>())*eve::log1p(az2);
      auto tmp =  kyosu::if_else( kyosu::is_real(z)
                                , kyosu::log(kyosu::real(z))
                                , z1
                                );
      return kyosu::if_else( kyosu::is_eqz(z)
                           , eve::minf(eve::as(az))
                           , tmp
                           );

     }
  }

  template<typename C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::sqrt> const&, C const& z) noexcept
  {
    if constexpr(kyosu::concepts::complex<C>)
    {
      //always compute the sqrt of the complex with positive imaginary part
      //then conjugate if necessary
      auto [rz, iz] = z;
      auto negimag = eve::is_negative(iz);
      auto x = eve::abs(rz);
      auto y = eve::abs(iz);
      auto iaz = eve::if_else(negimag, -iz, iz); // always >= 0 or -Nan
      auto gtxy = (x > y);
      auto gezrz = eve::is_gez(rz);
      auto r = eve::if_else(gtxy, y/x, x/y);
      auto rr= eve::sqrt(eve::inc(eve::sqr(r)));
      auto sqrtx = eve::sqrt(x);
      auto w = eve::if_else(gtxy,
                            sqrtx*eve::sqrt(eve::half(eve::as(r))*eve::inc(rr)),
                            eve::sqrt(y)*eve::sqrt(eve::half(eve::as(r))*(r+rr)));
      auto is_real_z = kyosu::is_real(z);
      C res;
      auto rr1 = eve::if_else(is_real_z, sqrtx, w);
      auto ii1 = eve::if_else(is_real_z, eve::zero, iaz*eve::half(eve::as(r))/w);
      res = kyosu::if_else(gezrz
                          , complex(rr1, ii1)
                          , complex(ii1, rr1)
                          );
      if (eve::any(is_not_finite(z))) [[unlikely]]
      {
        res = kyosu::if_else(rz == eve::minf(eve::as(rz))
                            , kyosu::if_else( eve::is_nan(iz), complex(iz, eve::minf(eve::as(rz)))
                                            , complex(eve::zero(eve::as(rz)), eve::inf(eve::as(rz))))
                            , res
                            );
        res = kyosu::if_else(rz == eve::inf(eve::as(rz))
                            , if_else( eve::is_nan(iz), complex(eve::inf(eve::as(rz)), iz)
                                     , complex( eve::inf(eve::as(rz)), eve::zero(eve::as(rz)) ))
                            , res
                            );
        res = kyosu::if_else(eve::is_nan(rz), complex(rz, rz), res);
        auto infty = eve::inf(eve::as(iaz));
        res = kyosu::if_else(iaz == infty,  complex(infty, infty), res);
      }
      return if_else(negimag, kyosu::conj(res), res);
    }
    else
    {
      auto r = kyosu::abs(z);
      auto theta = eve::acos(real(z)/r);
      auto u = kyosu::sign(kyosu::pure(z));
      auto [s, c] = eve::sincos(theta*eve::half(eve::as(theta)));
      auto res = u*s;
      kyosu::real(res) = c;
      return kyosu::if_else(eve::is_eqz(r), eve::zero(eve::as(z)), res*eve::sqrt(r));
    }
  }

  template<eve::floating_value T, typename ...Cs>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::lpnorm> const&, T const & p, Cs const &... zs) noexcept
  {
    if constexpr(sizeof...(zs) == 0) return 0.0f;
    if constexpr(sizeof...(zs) == 1) return kyosu::abs(zs...);
    else return eve::lpnorm(p, kyosu::abs(zs)...);
  }

  template<typename ...Cs>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::hypot> const&, Cs const &... zs) noexcept
  {
    if constexpr(sizeof...(zs) == 0) return 0.0f;
    if constexpr(sizeof...(zs) == 1) return kyosu::abs(zs...);
    else return eve::hypot(kumi::flatten(kumi::cat(zs...)));
  }

  template<typename ...Cs>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::manhattan> const&, Cs const &... zs) noexcept
  {
    if constexpr(sizeof...(zs) == 0) return 0.0f;
    else return eve::manhattan(kumi::flatten(kumi::cat(zs...)));
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::pow> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    using r_t = kyosu::as_cayley_dickson_t<C0,C1>;
    using er_t = eve::element_type_t<r_t>;
    using u_t  = eve::underlying_type_t<er_t>;
    if constexpr(eve::integral_value<C1>)
    {
      if constexpr( eve::unsigned_value<C1> )
      {
        C0 base = c0;
        C1 expo = c1;
        auto const o = eve::one(eve::as<u_t>());
        r_t result(o);
        while(true)
        {
          if  (eve::all(eve::is_eqz(expo))) break;
          result = kyosu::if_else(eve::is_odd(expo), result*base, o);
          expo = (expo >> 1);
          base = kyosu::sqr(base);
        }
        return result;
      }
      else
      {
        using ic1_t = eve::as_integer_t<C1, unsigned>;
        auto tmp = kyosu::pow(c0, eve::bit_cast(eve::abs(c1), eve::as<ic1_t>()));
        return kyosu::if_else(eve::is_ltz(c1), kyosu::rec(tmp), tmp);
      }
    }
    else if constexpr((dimension_v<C0> <= 2) && (dimension_v<C1> <= 2))
    {
      r_t r;
      if constexpr(eve::floating_value<C0> && kyosu::concepts::complex<C1>) // c1 is complex c0 is real
      {
        auto [rc1, ic1] = c1;
        auto lgac0 = eve::log_abs(c0);
        auto ang = eve::if_else(kyosu::is_real(c1), eve::zero, ic1*lgac0);
        auto mod = eve::pow(c0, rc1);
        auto r1 = kyosu::from_polar(mod, ang);
        auto isposc0 = eve::is_positive(c0);
        if (eve::all(isposc0))
        {
          r = r1;
        }
        else
        {
          auto rho = eve::exp(eve::diff_of_prod(lgac0, rc1, ic1, eve::pi(eve::as(rc1))));
          auto theta = eve::pedantic(eve::sum_of_prod)(eve::pi(eve::as(rc1)), rc1, ic1, lgac0);
          auto r2 = rho*kyosu::exp_i(theta);
          r = kyosu::if_else(isposc0, r1, r2);
        }
      }
      else if constexpr(eve::floating_value<C1> ) // c0 is complex c1 is real
      {
        auto lc0 = kyosu::log_abs(c0);
        auto argc0 = kyosu::arg(c0);
        auto rho = eve::exp(lc0*c1);
        auto theta = argc0*c1;
        return rho*kyosu::exp_i(theta);
      }
      else if constexpr( kyosu::concepts::complex<C0>)// c0 and c1 are complex
      {
//         auto   rc1 = real(c1);
//         auto   ic1 = imag(c1);
        auto  [rc1, ic1] = c1;
        auto lc0 = kyosu::log_abs(c0);
        auto argc0 = kyosu::arg(c0);
        auto rho = eve::exp(eve::pedantic(eve::diff_of_prod)(lc0, rc1, ic1, argc0));
        auto theta = eve::pedantic(eve::sum_of_prod)(argc0, rc1, ic1, lc0);
        r = rho*exp_i(theta);
        auto realc0 = is_real(c0);
        if(eve::any(realc0))
        {
          auto rr = kyosu::pow(real(c0), c1);
          r = kyosu::if_else(realc0, rr, r);
        }
      }
      r = kyosu::if_else(kyosu::is_eqz(c1), eve::one(eve::as<u_t>()), r);
      return r;
    }
    else
    {
      auto cc0 = kyosu::convert(c0, eve::as<er_t>());
      auto cc1 = kyosu::convert(c1, eve::as<er_t>());

      auto r = kyosu::exp(kyosu::log(cc0)*cc1);
      return kyosu::if_else (kyosu::is_eqz(cc0)
                            , eve::if_else(kyosu::is_eqz(cc1)
                                            , eve::one(eve::as<u_t>())
                                            , eve::zero(eve::as<u_t>()))
                            , r
                            );
    }
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::pow_abs> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    auto ac0 = kyosu::sqr_abs(c0);
    if constexpr(eve::ordered_value<C1>)
      return eve::pow(ac0, c1*eve::half(eve::as(ac0)));
    else
      return kyosu::pow(ac0, c1*eve::half(eve::as(ac0)));
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::powm1> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    return kyosu::dec(kyosu::pow(c0, c1));
  }

  template<typename  C0, typename  C1>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::pow1p> const&, C0 const & c0, C1 const &  c1) noexcept
  {
    return kyosu::pow(kyosu::inc(c0), c1);
  }
}
