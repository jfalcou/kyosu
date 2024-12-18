//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu::_
{

  ///////////////////////////////////////////////////////////////////////
  // new
  ///////////////////////////////////////////////////////////////////////

  template<int Kind, eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_ir(N n, Z z) noexcept
  {
    auto h =  eve::half(as<eve::underlying_type_t<Z>>());
    auto fac = sqrt(pio_2(as(real(z)))*rec(z));
    if constexpr(Kind == 1)
      return cb_ir(n+h, z)*fac;
    else
      return cb_ir(-n-h, z)*fac;
  }

  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_kr(N n, Z z) noexcept
  {
    auto h =  eve::half(as<eve::underlying_type_t<Z>>());
    auto fac = sqrt(pio_2(as(real(z)))*rec(z));
    return cb_kr(n+h, z)*fac;
  }

}
