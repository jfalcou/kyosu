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
  auto dispatch(eve::tag_of<kyosu::is_imag> const&, C const& c) noexcept
  {
    return eve::is_eqz(kyosu::real(c));
  }

}
