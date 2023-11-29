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

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
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
//     auto init = j;
//     auto jcur = jnext;
//     auto res = j;
//     for(int i=nn-1; i > 0 ; --i)
//     {
//       jcur = (2*i+1)*rz*j-jnext;
//       if(i == n+1) res = jcur;
//       jnext = j;
//       j = jcur;
//     }
    auto sj0ltsj1 = kyosu::abs(sj0) <= kyosu::abs(sj1);
    auto scalesj0 = (sj0/f1);
    auto scalesj1 = (sj1/f0);
    res *= if_else(sj0ltsj1, scalesj1, scalesj0);
    return if_else(is_eqz(z), eve::zero, res);
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

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
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

//Is it better ?
//     using u_t = eve::underlying_type_t<Z>;
//     auto imzge0 = eve::is_gez(imag(z));
//     auto jn = sb_jn(n, z);
//     auto i = complex(u_t(0), u_t(1));
//     Z res;
//     if (eve::any(imzge0))
//     {
//       auto z1 = if_else(imzge0, z, conj(z));
//       res = jn-sph_bessel_h1n(n, z1);
//     }
//     if (!eve::all(imzge0))
//     {
//       auto z2 = if_else(imzge0, conj(z), z);
//       res = if_else(imzge0,  res, sph_bessel_h2n(n, z2)-jn);
//     }
//     return complex(-imag(res), real(res));
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto sb_jyn(N n, Z z, R & sjs, R& sys) noexcept
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
    auto sy0 = sb_y0(z);
    sjs[0] = sj0;
    sys[0] = sy0;
    if (n == 0) return kumi::tuple(sj0, sy0);
    auto sj1 = sb_j1(z);
    auto sy1 = sb_y1(z);
    sjs[1] = sj1;
    sys[1] = sy1;
    if (n == 1) return kumi::tuple(sj1, sy1);

    auto rz = kyosu::rec(z);
    auto nn = bd(n);
    // compute sj(i, z) 0 <= i <= n;
    Z jnext(kyosu::complex(u_t(0)));
    Z j(kyosu::complex(eve::sqrtsmallestposval(eve::as<u_t>())));
    auto jcur = jnext;
    for(int i=nn-1; i > 0 ; --i)
    {
      jcur = (2*i+1)*rz*j-jnext;
      if(i <= n) sjs[n] = j;
      jnext = j;
      j = jcur;
    }
    auto sj0ltsj1 = kyosu::abs(sj0) <= kyosu::abs(sj1);
    auto scalej0 = (sj0/jcur);
    auto scalej1 = (sj1/jnext);
    auto scale = if_else(sj0ltsj1, scalej0, scalej1);
    sjs[0] = if_else(is_eqz(z), eve::one, sjs[0] * scale);
    for(int i=1; i < n; ++i)  sjs[i] = if_else(is_eqz(z), eve::zero, sjs[i] * scale);
    // compute sy(i, z) 0 <= i <= n; by forward recurrence
    for(int i=2; i < n ; ++i)
    {
      sys[i] = dec(2*i)*sys[i-1]*rz-sys[i-2];
    }
    return kumi::tuple(sjs[n], sys[n]);
  }


  ////////////////////////////////////////////////////////////
  // end utilities
  ////////////////////////////////////////////////////////////

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j0>, Z z) noexcept
  {
    return sb_j0(z);
  }

  template<typename Z>
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

  template<eve::integral_scalar_value N, typename Z>
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

  template<typename Z>
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

  template<typename Z>
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

  template<eve::integral_scalar_value N, typename Z>
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
}
