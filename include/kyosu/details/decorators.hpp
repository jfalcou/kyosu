//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/detail/raberu.hpp>

namespace kyosu
{
  struct assume_unitary_mode    {};

  [[maybe_unused]] inline constexpr auto assume_unitary  = ::rbr::flag(assume_unitary_mode{});

  struct assume_unitary_option : eve::detail::exact_option<assume_unitary>      {};

}
