//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/abi.hpp>
#include <eve/traits/overload.hpp>

namespace kyosu::_    { EVE_CALLABLE_NAMESPACE(); }

//  EVE-related macro that use kyosu::_ as the deferred namespace
#define KYOSU_CALLABLE_OBJECT(TYPE, NAME) EVE_CALLABLE_OBJECT_FROM(kyosu::_,TYPE, NAME)
#define KYOSU_CALL(...)                   EVE_DISPATCH_CALL(__VA_ARGS__)
#define KYOSU_DELAY()                     EVE_REQUIRES(eve::cpu_)
