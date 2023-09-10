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
  template < int N >  struct axis:std::integral_constant<int, N>{};
  template < bool E > struct ext:std::integral_constant<bool, E>{};
  template < bool E > struct norming:std::integral_constant<bool, E>{};
}

namespace kyosu
{

  inline constexpr auto _X(kyosu::_::axis<1>{});
  inline constexpr auto _Y(kyosu::_::axis<2>{});
  inline constexpr auto _Z(kyosu::_::axis<3>{});

  inline constexpr kyosu::_::ext<true>  extrinsic = {};
  inline constexpr kyosu::_::ext<false> intrinsic = {};
  inline constexpr kyosu::_::norming<false> assume_normalized = {};
  inline constexpr kyosu::_::norming<true>  normalize = {};
}
