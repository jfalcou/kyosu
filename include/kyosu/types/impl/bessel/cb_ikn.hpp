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
#include <kyosu/details/with_alloca.hpp>

namespace kyosu::_
{
  /////////////////////////////////
  //needed by the implementations of
  // cyl_bessel_i0
  // cyl_bessel_i1
  // cyl_bessel_in
  // cyl_bessel_k0
  // cyl_bessel_k1
  // cyl_bessel_kn
  // cyl_bessel_ikn
  /////////////////////////////////
  // utilities
  // cb_i0
  // cb_i1
  // cb_k0
  // cb_k1
  // cb_ikn
  ////////////////////////////////
  // no heap allocation is done by these functions
  // cyl_bessel_jyn computes all  j_i(z) and y_i(z) for 0 <= i <= n if n >= 0 (resp n <= i <= 0 if n <= 0)
  // and put the result in two ranges that are to be allocated by the caller.
  // call to cyl_bessel_jn and cyl_bessel_yn that need calling cyl_bessel_jyn do an internal quick allocaton
  // on the stack using __builtin_alloca_with_align.

  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------
  //  utilities
  //===-------------------------------------------------------------------------------------------
  //===-------------------------------------------------------------------------------------------

//===-------------------------------------------------------------------------------------------
  //  cb_i0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto cb_i0(Z z) noexcept
  {
    return  cb_j0(muli(z));
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_i1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto cb_i1(Z z) noexcept
  {
    return mulmi(cb_j1(muli(z)));
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_k0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto cb_k0(Z z) noexcept
  {
    auto ipiotwo = muli(kyosu::pio_2(eve::as<Z>()));
    auto argzlt0 = eve::is_ltz(arg(z));
    auto r = if_else(argzlt0
                    , cb_h1_0(muli(z))
                    , -cb_h2_0(mulmi(z))
                    );
    r*= ipiotwo;
    return if_else(is_eqz(z), complex(kyosu::inf(eve::as<Z>())), r);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_k1
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto cb_k1(Z z) noexcept
  {
    auto mpiotwo = -kyosu::pio_2(eve::as<Z>());
    auto argzlt0 = eve::is_ltz(arg(z));
    auto r = if_else(argzlt0
                    , cb_h1_1(muli(z))
                    , cb_h2_1(mulmi(z))
                    );
      r *= mpiotwo;
      return if_else(is_eqz(z), complex(kyosu::inf(eve::as<Z>())), r);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_in
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
  //  cb_kn
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
                     , cpi*cb_h1n(n, z*epio2)
                     , cmi*cb_h2n(n, z*empio2));
    return if_else(is_eqz(z), complex(eve::inf(eve::as<u_t>())), r);
  }

  //===-------------------------------------------------------------------------------------------
  //  cb_ikn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z, std::size_t S> KYOSU_FORCEINLINE
  auto cb_ikn(N n, Z z, std::span<Z, S> is, std::span<Z, S> ks) noexcept
  requires(concepts::complex<Z> || concepts::real<Z>)
  {
    using u_t = eve::underlying_type_t<Z>;
    auto nn =  eve::abs(n);
    EVE_ASSERT(N(size(is)) > nn, "not room enough in is");
    EVE_ASSERT(N(size(ks)) > nn, "not room enough in ks");
    auto sn = sign(n);
    for(N j=0; j <= nn; j = j++)
    {
      is[j] = cb_in(sn*j, z);
      ks[j] = cb_kn(sn*j, z);
    }
    return kumi::tuple{is[nn], ks[nn]};
  }
}
