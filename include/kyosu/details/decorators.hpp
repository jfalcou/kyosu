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
  struct intrinsic_mode         {};
  struct extrinsic_mode         {};

  [[maybe_unused]] inline constexpr auto assume_unitary  = ::rbr::flag(assume_unitary_mode{});
  [[maybe_unused]] inline constexpr auto intrinsic  = ::rbr::flag(intrinsic_mode{});
  [[maybe_unused]] inline constexpr auto extrinsic  = ::rbr::flag(extrinsic_mode{});

  struct assume_unitary_option : eve::detail::exact_option<assume_unitary>      {};
  struct intrinsic_option : eve::detail::exact_option<intrinsic>                {};
  struct extrinsic_option : eve::detail::exact_option<extrinsic>                {};

}
