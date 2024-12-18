//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/bessel/bessel_utils2.hpp>
#include <kyosu/details/with_alloca.hpp>
#include <kyosu/details/bessel/besseln/cb_hn.hpp>
namespace kyosu::_
{
  /////////////////////////////////
  // utilities
  // cb_in
  // cb_kn
  //////ikn
  /////////////////////////////////

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  utilities
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

  //===-------------------------------------------------------------------------------------------
  //  cb_in just last
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_in(N n, Z z) noexcept
  {
    using e_t = as_real_type_t<Z>;
    auto miton = [](N n){
      if (n%4 == 0) return complex(eve::one(eve::as<e_t>()));
      else if (n%4 == 1) return  complex(eve::zero(eve::as<e_t>()), eve::mone(eve::as<e_t>()));
      else if (n%4 == 2) return complex(eve::mone(eve::as<e_t>()));
      else return complex(eve::zero(eve::as<e_t>()), eve::one(eve::as<e_t>()));
    };
    auto an =  eve::abs(n);
    return miton(an)*cb_jn(an,muli(z));
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_kn just last
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto cb_kn(N n, Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto argz = arg(z);
    n =  eve::abs(n);
    auto piotwo = eve::pio_2(eve::as<u_t>());
    auto i = complex(u_t(0), u_t(1));
    auto cpi = piotwo*i*exp_ipi(u_t(n)/2);
    auto cmi = -piotwo*i*exp_ipi(-u_t(n)/2);
    auto epio2 = exp_ipi(eve::half(eve::as<u_t>()));
    auto empio2 = exp_ipi(eve::mhalf(eve::as<u_t>()));
    auto argzlt0 = eve::is_ltz(argz);
    auto r =  if_else(argzlt0
                     , cpi*cb_hn<1>(n, z*epio2)
                     , cmi*cb_hn<2>(n, z*empio2));
    return if_else(is_eqz(z), complex(eve::inf(eve::as<u_t>())), r);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_ikn suppose allocatied is and ks
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, typename R1, typename R2>
  KYOSU_FORCEINLINE  auto cb_ikn(N n, Z z, R1& is, R2& ks) noexcept
  requires(concepts::complex<Z> || concepts::real<Z>)
  {
    using u_t = eve::underlying_type_t<Z>;
    auto nn =  eve::abs(n);
    //    nn = eve::min(n, N(is.size()), N(ks.size()));
    auto sn = sign(n);
    for(N j=0; j <= nn; j = j++)
    {
      is[j] = cb_in(sn*j, z);
      ks[j] = cb_kn(sn*j, z);
    }
    return kumi::tuple{is[nn], ks[nn]};
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_in all possible up to ris size or n
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, std::size_t S>
  Z cb_in(N n, Z z, std::span<Z, S> ris)
  {
    using e_t = as_real_type_t<Z>;
    auto miton = [](N n){
      if (n%4 == 0) return complex(eve::one(eve::as<e_t>()));
      else if (n%4 == 1) return  complex(eve::zero(eve::as<e_t>()), eve::mone(eve::as<e_t>()));
      else if (n%4 == 2) return complex(eve::mone(eve::as<e_t>()));
      else return complex(eve::zero(eve::as<e_t>()), eve::one(eve::as<e_t>()));
    };
    std::size_t an =  eve::abs(n);
    auto jn = cb_jn(an, muli(z), ris);
    auto nn = eve::min(size(ris), an);
    for(int i=1; i < nn; ++i) ris[i]*= miton(i);
    return jn*miton(n);
  }
}
