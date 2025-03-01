//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu::_
{
  auto EVE_FORCEINLINE is_negint(auto n)
  {
    return kyosu::is_real(n) && eve::is_flint(real(n)) && eve::is_lez(real(n));
  }
}
