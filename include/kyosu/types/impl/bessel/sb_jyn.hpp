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
#include <kyosu/types/impl/bessel/cb_jyn.hpp>
namespace kyosu::_
{

  /////////////////////////////////
  // contains implementations of
  // sph_bessel_j0
  // sph_bessel_j1
  // sph_bessel_y0
  // sph_bessel_y1
  // sph_bessel_jyn
  /////////////////////////////////
  // utilities
  // sb_j0
  // sb_j1
  // sb_y0
  // sb_y1
  // sb_jyn
  ////////////////////////////////

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_j0(Z z) noexcept
  {
    return sinc(z);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_j1(Z z) noexcept
  {
    auto rz = rec(z);
    return if_else(kyosu::abs(z) < eve::eps(eve::as(real(z)))
                  , eve::zero
                  , (sinc(z)-cos(z))*rz
                  );
  }

  template<eve::integral_scalar_value N, typename Z>
  auto sb_jn(N n, Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto bd = [z](int n){
      auto st = eve::abs(eve::sin(eve::abs(arg(z))));
      auto r  = kyosu::abs(z);
      auto m = eve::maximum(eve::ceil((u_t(1.83)+u_t(4.1)*eve::pow(st, u_t(0.33)))*
                                      eve::pow(r, (u_t(0.91)-u_t(0.43)*eve::pow(st, u_t(0.36))))+9*(1-eve::sqrt(st))));
      auto nn = (eve::any(is_real(z))) ? n+5 : n;
      return eve::max(nn, int(inc(m)));
    };

    auto sj0 = sb_j0(z);
    if (n == 0) return sj0;
    auto sj1 = sb_j1(z);
    if (n == 1) return sj1;
    // now n >= 2
    auto rz = kyosu::rec(z);
    auto nn = bd(n);
    Z f0(eve::zero(as<Z>()));
    Z f1(kyosu::complex(eve::sqrtsmallestposval(eve::as<Z>())));
    auto res = f1;
    for(int k=nn; k >= 0 ; --k)
    {
      auto f = (2*k+3)*f1*rz-f0;
      if(k ==  n) res = f;
      f0 = f1;
      f1 = f;
    }

    auto sj0ltsj1 = kyosu::abs(sj0) <= kyosu::abs(sj1);
    auto scalesj0 = (sj0/f1);
    auto scalesj1 = (sj1/f0);
    res *= if_else(sj0ltsj1, scalesj1, scalesj0);
    return if_else(is_eqz(z), eve::zero, res);
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto sb_jn(N n, Z z, R & sjs) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto bd = [z](int n){
      auto st = eve::abs(eve::sin(eve::abs(arg(z))));
      auto r  = kyosu::abs(z);
      auto m = eve::maximum(eve::ceil((u_t(1.83)+u_t(4.1)*eve::pow(st, u_t(0.33)))*
                                      eve::pow(r, (u_t(0.91)-u_t(0.43)*eve::pow(st, u_t(0.36))))+9*(1-eve::sqrt(st))));
      auto nn = (eve::any(is_real(z))) ? n+5 : n;
      return eve::max(nn, int(inc(m)));
    };

    auto sj0 = sb_j0(z);
    sjs[0] = sj0;
    if (n == 0) return sjs[0];
    auto sj1 = sb_j1(z);
    sjs[1] = sj1;
    if (n == 1) return sjs[1];
    // now n >= 2
    auto rz = kyosu::rec(z);
    auto nn = bd(n);
    Z f0(eve::zero(as<Z>()));
    Z f1(kyosu::complex(eve::sqrtsmallestposval(eve::as<Z>())));
    for(int k=nn; k >= 0 ; --k)
    {
      auto f = (2*k+3)*f1*rz-f0;
      if(k <=  n) sjs[k] = f;
      f0 = f1;
      f1 = f;
    }

    auto sj0ltsj1 = kyosu::abs(sj0) <= kyosu::abs(sj1);
    auto scalesj0 = (sj0/f1);
    auto scalesj1 = (sj1/f0);
    auto scale = if_else(sj0ltsj1, scalesj0, scalesj1);
    sjs[0] = sj0;
    sjs[1] = sj1;
    for(int i=2; i <= n; ++i)  sjs[i] = if_else(is_eqz(z), eve::zero, sjs[i] * scale);
    return sjs[n];
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_y0(Z z) noexcept
  {
    return -cos(z)/z;
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_y1(Z z) noexcept
  {
    return -cos(z)/sqr(z)-sinc(z);
  }

  template<eve::integral_scalar_value N, typename Z>
  auto sb_yn(N n, Z z) noexcept
  {
    auto rz = rec(z);
    auto sypred = sb_y0(z);
    if (n == 0) return sypred;
    auto sycur = sb_y1(z);
    if (n == 1) return sycur;
    for(int i=2; i <= n ; ++i)
    {
      auto synext = dec(2*i)*sycur*rz-sypred;
      sypred = sycur;
      sycur = synext;
    }
    return sycur;
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto sb_yn(N n, Z z, R& sys) noexcept
  {
    sys[0] = sb_y0(z);
    if (n == 0) return sys[0];
    sys[1] = sb_y1(z);
    if (n == 1) return sys[1];
    auto rz = kyosu::rec(z);
    // compute sy(i, z) 0 <= i <= n; by forward recurrence
    for(int i=2; i <= n ; ++i) sys[i] = dec(2*i)*sys[i-1]*rz-sys[i-2];
    return sys[n];
  }

  template<eve::integral_scalar_value N, typename Z, typename R1, typename R2>
  auto sb_jyn(N n, Z z, R1 & sjs, R2& sys) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto bd = [z](int n){
      auto st = eve::abs(eve::sin(eve::abs(arg(z))));
      auto r  = kyosu::abs(z);
      auto m = eve::maximum(eve::ceil((u_t(1.83)+u_t(4.1)*eve::pow(st, u_t(0.33)))*
                                      eve::pow(r, (u_t(0.91)-u_t(0.43)*eve::pow(st, u_t(0.36))))+9*(1-eve::sqrt(st))));
      auto nn = (eve::any(is_real(z))) ? n+5 : n;
      return eve::max(nn, int(inc(m)));
    };

    auto sj0 = sb_j0(z);
    sjs[0] = sj0;
    sys[0] = sb_y0(z);
    if (n == 0) return  kumi::tuple{sjs[0], sys[0]};
    auto sj1 = sb_j1(z);
    sjs[1] = sj1;
    sys[1] = sb_y1(z);
    if (n == 1) return kumi::tuple{sjs[1], sys[1]};
    // now n >= 2
    auto rz = kyosu::rec(z);
    auto nn = bd(n);
    Z f0(eve::zero(as<Z>()));
    Z f1(kyosu::complex(eve::sqrtsmallestposval(eve::as<Z>())));
    for(int k=nn; k >= 0 ; --k)
    {
      auto f = (2*k+3)*f1*rz-f0;
      if(k <=  n) sjs[k] = f;
      f0 = f1;
      f1 = f;
    }

    auto sj0ltsj1 = kyosu::abs(sj0) <= kyosu::abs(sj1);
    auto scalesj0 = (sj0/f1);
    auto scalesj1 = (sj1/f0);
    auto scale = if_else(sj0ltsj1, scalesj0, scalesj1);
    sjs[0] = sj0;
    sjs[1] = sj1;
    for(int i=2; i <= n; ++i)  sjs[i] = if_else(is_eqz(z), eve::zero, sjs[i] * scale);
    // compute sy(i, z) 0 <= i <= n; by forward recurrence
    for(int i=2; i <= n ; ++i) sys[i] = dec(2*i)*sys[i-1]*rz-sys[i-2];
    return kumi::tuple{sjs[n], sys[n]};
  }

  ////////////////////////////////////////////////////////////
  // end utilities
  ////////////////////////////////////////////////////////////

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j0>, Z z) noexcept
  {
    return sb_j0(z);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_j1(z);
    }
    else
    {
      return cayley_extend(sph_bessel_j1, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_jn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_jn(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_jn, n, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_jn>, N n, Z z, R& sjs) noexcept
  {
    return sb_jn(n, z, sjs);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_y0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
     return sb_y0(z);
    }
    else
    {
      return cayley_extend(sph_bessel_y0, z);
    }
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_y1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_y1(z);
    }
    else
    {
      return cayley_extend(sph_bessel_y1, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_yn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_yn(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_yn, n, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_yn>, N n, Z z, R& sys) noexcept
  {
    return sb_yn(n, z, sys);
  }

  template<eve::integral_scalar_value N, typename Z, typename R1,  typename R2> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_jyn>, N n, Z z, R1& sjs, R2& sys) noexcept
  {
      return sb_jyn(n, z, sjs, sys);
  }
}
