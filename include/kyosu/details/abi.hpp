//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

// Faster than std::forward
#define KYOSU_FWD(...) EVE_FWD(__VA_ARGS__)
#define KYOSU_ABI EVE_ABI
#define KYOSU_NOINLINE EVE_NOINLINE
