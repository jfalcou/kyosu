//======================================================================================================================
/*
  Kyosu - Complex Math Made Easy
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

// Faster than std::forward
#define KYOSU_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)
