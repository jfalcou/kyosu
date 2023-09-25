//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace kyosu::_
{
  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::to_polar> const&, C const& c) noexcept
  {
    return kumi::tuple{kyosu::abs(c),  kyosu::arg(c)};
  }

}
