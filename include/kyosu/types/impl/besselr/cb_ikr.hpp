//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/types/impl/detail/bessel_utils2.hpp>
#include <kyosu/types/impl/bessel/cb_jyn.hpp>
#include <kyosu/types/impl/besselr/cb_jyr01.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <vector>

namespace kyosu::_
{
  /////////////////////////////////
  // contains implementations of
  // cyl_bessel_i
  // cyl_bessel_k
  // cyl_bessel_ik
  /////////////////////////////////
  // utilities
  // cb_ir
  // cb_kr

  //===-------------------------------------------------------------------------------------------
  //  cb_ir n outputs
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto cb_ir(N v, Z z, R& is) noexcept
  {
    //DLMF 10.27.6 with conjugation for arg(z) > 0
    using e_t = as_real_type_t<Z>;
    auto argzpos = eve::is_gtz(kyosu::arg(z));
    z = if_else(argzpos, conj(z), z);
    cyl_bessel_j(v, muli(z), is);
    auto n = int(v);
    auto v0 = v-n;
    auto an = eve::abs(n);
    auto vi = v0;
    auto sgn = v0 > 0 ? 1 :-1;
    for(int i=0; i <= an ; ++i)
    {
      auto fac = exp_ipi(-vi/2);
      vi+= sgn;
      is[i]*= fac;
      is[i] = if_else(argzpos, conj(is[i]), is[i]);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_ir just last
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_ir(N v, Z z) noexcept
  {
    using e_t = as_real_type_t<Z>;
    auto fac = exp_ipi(-v/2);
    return fac*cyl_bessel_j(v,muli(z));
  }


  //===-------------------------------------------------------------------------------------------
  //  cb_kr just last
  //===-------------------------------------------------------------------------------------------

  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_kr(N v, Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto argz = arg(z);
    auto piotwo = eve::pio_2(eve::as<u_t>());
    auto i = complex(u_t(0), u_t(1));
    auto f = muli(exp_ipi(v/2));
    auto cpi = piotwo*f;
    auto cmi = piotwo*rec(f);
    auto argzlt0 = eve::is_ltz(argz);
    auto r =  if_else(argzlt0
                     , cpi*cyl_bessel_h1(v, muli(z))
                     , cmi*cyl_bessel_h2(v, mulmi(z))
                     );
    return if_else(is_eqz(z), complex(eve::inf(eve::as<u_t>())), r);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_kr n outputs
  //===-------------------------------------------------------------------------------------------

   template<eve::floating_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto cb_kr(N v, Z z, R& ks) noexcept
  requires(concepts::complex<Z> || eve::floating_ordered_value<Z>)
  {
    using u_t = eve::underlying_type_t<Z>;
    auto n = int(v);
    auto v0 = v-n;
    auto an = eve::abs(n);
    auto vi = v0;
    auto inc = (v > 0) ? 1 : -1;
    for(int j=0; j <= an; ++j)
    {
      ks[j] = cb_kr(vi, z);
      vi+= inc;
    }
    return ks[n];
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_i
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i>, N v, Z z, R & is) noexcept
  {
    return cb_ir(v, z, is);
  }

  template<eve::floating_scalar_value N, kyosu::concepts::complex Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_i>, N v, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_ir(v, z);
    }
    else
    {
      return cayley_extend(cyl_bessel_i, v, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_k 
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_k>, N v, Z z, R & ks) noexcept
  {
    return cb_kr(v, z, ks);
  }

  template<eve::floating_scalar_value N, kyosu::concepts::complex Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_k>, N v, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return cb_kr(v, z);
    }
    else
    {
      return cayley_extend(cyl_bessel_k, v, z);
    }
  }


  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_ik
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, kyosu::concepts::complex Z, typename R1, typename R2>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_k>, N v, Z z, R1 & is, R2& ks) noexcept
  {
    return kumi::tuple{cb_kr(v, z, is), cb_kr(v, z, ks)};
  }

}
