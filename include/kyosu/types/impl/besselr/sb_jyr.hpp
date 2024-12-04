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

  //===-------------------------------------------------------------------------------------------
  //  sb_jr all
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, std::size_t S> KYOSU_FORCEINLINE
  auto sb_jr(N n, Z z, std::span<Z, S> vjs) noexcept
  {
    auto fac = sqrt(pio_2(as(real(z)))*rec(z));
    auto v = n+eve::half(eve::as<eve::underlying_type_t<Z>>());
    auto r = _::cb_jr(v, z, vjs);
    for(int i = 0; i < size(vjs); ++i) vjs[i]*= fac;
    return fac*r;
  }


  //===-------------------------------------------------------------------------------------------
  //  sb_jr just last
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_jr(N n, Z z) noexcept
  {
    std::array<Z, 0> dummy;
    return sb_jr(n, z, std::span(dummy));
  }

}
