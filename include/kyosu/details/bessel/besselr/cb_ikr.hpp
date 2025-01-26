//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/bessel/bessel_utils2.hpp>
#include <kyosu/details/bessel/besseln/cb_jyn.hpp>
#include <kyosu/details/bessel/besselr/cb_jyr01.hpp>
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{
  /////////////////////////////////
  // utilities
  // cb_ir
  // cb_kr
  /////////////////////////////////

  //===-------------------------------------------------------------------------------------------
  //  cb_kr just last
  //===-------------------------------------------------------------------------------------------

  template<eve::floating_scalar_value N, typename Z>
  auto cb_kr(N v, Z z) noexcept
  {
    v = eve::abs(v); //K(-v, z) == K(v, z) DLMF 10.27.1
    using u_t = eve::underlying_type_t<Z>;
    auto argz = arg(z);
    auto piotwo = eve::pio_2(eve::as<u_t>());
    auto i = complex(u_t(0), u_t(1));
    auto f = muli(exp_ipi(v/2));
    auto cpi = piotwo*f;
    auto cmi = piotwo*rec(f);
    auto argzlt0 = eve::is_ltz(argz);
    auto r =  if_else(argzlt0
                     , cpi*cb_h1r(v, muli(z))
                     , cmi*cb_h2r(v, mulmi(z))
                     );
    return if_else(is_eqz(z), complex(eve::inf(eve::as<u_t>())), r);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_kr all possible outputs
  //===-------------------------------------------------------------------------------------------

  template<eve::floating_scalar_value N, typename Z, typename R>
  auto cb_kr(N v, Z z, R& ks) noexcept
  {
    v = eve::abs(v);  //k(-v, z) == K(v, z) DLMF 10.27.1
    using u_t = eve::underlying_type_t<Z>;
    auto n = std::size_t(v); //n>= 0
    auto v0 = v-n;
    auto vi = v0;
    for(int j=0; j < eve::min(size_t(n+1), size(ks)); ++j)
    {
      ks[j] = cb_kr(vi, z);
      vi = eve::inc(vi);
    }
    return cb_kr(v0+n, z);
  }

 //===-------------------------------------------------------------------------------------------
  //  cb_ir n outputs
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, typename R>
  Z cb_ir(N v, Z z, R& cis) noexcept
  {
    size_t an = eve::abs(int(v));
    auto doit =  [an, v, &z, &cis](auto is){
      //DLMF 10.27.6 with conjugation for arg(z) > 0
      if (v > 0)
      {
        auto argzpos = eve::is_gtz(kyosu::arg(z));
        z = if_else(argzpos, conj(z), z);
        cb_jr(v, muli(z), is);
        auto v0 = v-an;
        auto vi = v0;
        for(int i=0; i <= an ; ++i)
        {
          auto fac = exp_ipi(-vi/2);
          vi =  inc(vi);
          is[i]*= fac;
          is[i] = if_else(argzpos, conj(is[i]), is[i]);
        }
      }
      else
      {
        cb_ir(-v, z, is);
        auto mvi = frac(-v);
        auto spv = eve::sinpi(mvi);
        for(size_t l=0; l <= an; ++l)
        {
          is[l] += kyosu::two_o_pi(as(z))*spv*cb_kr(mvi, z);
          mvi = inc(mvi);
          spv = -spv;
        }
      }
      for(int i=0; i < eve::min(size(cis), an+1); ++i) cis[i] = is[i];
      return is[an];
    };
    return with_alloca<Z>(an+1, doit);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_ir just last
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z>
  auto cb_ir(N v, Z z) noexcept
  {
    if (v >= 0)
    {
      auto argzpos = eve::is_gtz(kyosu::arg(z));
      z = if_else(argzpos, conj(z), z);
      auto fac = exp_ipi(-v/2);
      auto r = fac*_::cb_jr(v,kyosu::muli(z));
      return if_else(argzpos, conj(r), r);
    }
    else
    {
      auto mv = -v;
      return cb_ir(mv, z)+kyosu::two_o_pi(as(z))*sinpi(mv)*cb_kr(mv, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_ik
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, typename R1, typename R2> KYOSU_FORCEINLINE
  auto cb_ik(N v, Z z, R1& is, R2& ks) noexcept
  {
    auto in = cb_ir(v, z, is);
    auto kn = cb_kr(v, z, ks);
    return kumi::tuple{in, kn};
  }

}
