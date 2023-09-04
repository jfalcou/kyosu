//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>

namespace kyosu::_
{
  template<kyosu::concepts::complex C>
  KYOSU_FORCEINLINE constexpr
  auto dispatch(eve::tag_of<kyosu::arg> const&, C const& c) noexcept
  {
    return eve::pedantic(eve::atan2(kyosu::imag(c), kyosu::real(c));
  }
}
