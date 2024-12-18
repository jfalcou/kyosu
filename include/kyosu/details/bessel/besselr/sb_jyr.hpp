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
    auto dummy = std::span<Z, 0>();
    return sb_jr(n, z, dummy);
  }


   //===-------------------------------------------------------------------------------------------
  //  sb_yr all
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z, std::size_t S> KYOSU_FORCEINLINE
  auto sb_yr(N n, Z z, std::span<Z, S> vys) noexcept
  {
    auto fac = sqrt(pio_2(as(real(z)))*rec(z));
    auto v = n+eve::half(eve::as<eve::underlying_type_t<Z>>());
    auto r = _::cb_yr(v, z, vys);
    for(int i = 0; i < size(vys); ++i) vys[i]*= fac;
    return fac*r;
  }

  //===-------------------------------------------------------------------------------------------
  //  sb_yr just last
  //===-------------------------------------------------------------------------------------------
  template<eve::floating_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_yr(N n, Z z) noexcept
  {
     auto dummy = std::span<Z, 0>();
   return sb_yr(n, z, dummy);
  }
}
