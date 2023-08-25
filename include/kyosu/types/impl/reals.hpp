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
  template<eve::floating_value T>
  constexpr auto to_complex_(EVE_EXPECTS(eve::cpu_), T r)         noexcept  { return as_cayley_dickson_n_t<2,T>(r, 0); }

  template<eve::floating_value T0, eve::floating_value T1>
  constexpr auto to_complex_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i)  noexcept -> as_cayley_dickson_n_t<2,decltype(eve::add(r, i))>
  {
    return as_cayley_dickson_n_t<2, decltype(eve::add(r, i))>{r, i};
  }

  template<concepts::complex T>
  constexpr auto to_complex_(EVE_EXPECTS(eve::cpu_), T const& v)  noexcept  { return v; }
}
