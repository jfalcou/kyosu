//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/muli.hpp>

namespace kyosu::_
{

  template<eve::callable_options O, typename N> EVE_FORCEINLINE auto branch_correction(N n)
  {
    if constexpr (!O::contains(radpi)) return muli(eve::two_pi(eve::as(n)) * n);
    else return muli(2 * n);
  };

};
