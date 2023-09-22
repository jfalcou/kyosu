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
  constexpr auto complex_(EVE_EXPECTS(eve::cpu_), T r)         noexcept  { return as_cayley_dickson_n_t<2,T>(r, 0); }

  template<eve::floating_value T0, eve::floating_value T1>
  constexpr auto complex_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i)  noexcept -> as_cayley_dickson_n_t<2,decltype(eve::add(r, i))>
  {
    return as_cayley_dickson_n_t<2, decltype(eve::add(r, i))>{r, i};
  }

  template<concepts::complex T>
  constexpr auto complex_(EVE_EXPECTS(eve::cpu_), T const& v)  noexcept  { return v; }

  //=========================================================================================================================

  template<eve::floating_value T>
  constexpr auto quaternion_(EVE_EXPECTS(eve::cpu_), T r)         noexcept  { return as_cayley_dickson_n_t<4,T>(r, 0, 0, 0); }

  template<eve::floating_value T0, eve::floating_value T1>
  constexpr auto quaternion_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i)  noexcept -> as_cayley_dickson_n_t<4, decltype(eve::add(r, i))>
  {
    return as_cayley_dickson_n_t<4, decltype(eve::add(r, i))>{r, i, 0, 0};
  }

  template<eve::floating_value T0, eve::floating_value T1, eve::floating_value T2, eve::floating_value T3>
  constexpr auto quaternion_(EVE_EXPECTS(eve::cpu_), T0 r, T1 i, T2 j, T3 k)  noexcept -> as_cayley_dickson_n_t<4, decltype(eve::add(r, i, j, k))>
  {
    return as_cayley_dickson_n_t<4, decltype(eve::add(r, i, j, k))>{r, i, j, k};
  }

  template<concepts::complex T0>
  constexpr auto quaternion_(EVE_EXPECTS(eve::cpu_), T0 const & c0)  noexcept
  {
    return as_cayley_dickson_n_t<4, decltype(eve::add(get<0>(c0), get<1>(c0)))>(get<0>(c0), get<1>(c0), 0, 0);
  }

  template<concepts::complex T0,concepts::complex T1>
  constexpr auto quaternion_(EVE_EXPECTS(eve::cpu_), T0 const & c0, T1 const & c1)  noexcept
  {
    return as_cayley_dickson_n_t<4, decltype(eve::add(get<0>(c0), get<1>(c0),get<0>(c1), get<1>(c1)))>(get<0>(c0), get<1>(c0),get<0>(c1), get<1>(c1));
  }

  template<concepts::quaternion T>
  constexpr auto quaternion_(EVE_EXPECTS(eve::cpu_), T const& v)  noexcept
  {
    return v;
  }

}
