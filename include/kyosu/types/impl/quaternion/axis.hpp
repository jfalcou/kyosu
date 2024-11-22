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
}

namespace kyosu
{

  inline constexpr auto X_(kyosu::_::axis<1>{});
  inline constexpr auto Y_(kyosu::_::axis<2>{});
  inline constexpr auto Z_(kyosu::_::axis<3>{});
}
