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
  struct extrinsic_mode         {};
  struct flat_mode              {};
  struct incomplete_mode        {};
  struct intrinsic_mode         {};
  struct kind_1_mode            {};
  struct kind_2_mode            {};
  struct regularized_mode       {};
  struct type_1_mode            {};
  struct type_2_mode            {};
  struct type_3_mode            {};

  [[maybe_unused]] inline constexpr auto assume_unitary  = ::rbr::flag(assume_unitary_mode{});
  [[maybe_unused]] inline constexpr auto intrinsic       = ::rbr::flag(intrinsic_mode{});
  [[maybe_unused]] inline constexpr auto extrinsic       = ::rbr::flag(extrinsic_mode{});
  [[maybe_unused]] inline constexpr auto flat            = ::rbr::flag(flat_mode{});
  [[maybe_unused]] inline constexpr auto incomplete      = ::rbr::flag(incomplete_mode{});
  [[maybe_unused]] inline constexpr auto kind_1          = ::rbr::flag(kind_1_mode{});
  [[maybe_unused]] inline constexpr auto kind_2          = ::rbr::flag(kind_2_mode{});
  [[maybe_unused]] inline constexpr auto regularized     = ::rbr::flag(regularized_mode{});
  [[maybe_unused]] inline constexpr auto type_1          = ::rbr::flag(type_1_mode{});
  [[maybe_unused]] inline constexpr auto type_2          = ::rbr::flag(type_2_mode{});
  [[maybe_unused]] inline constexpr auto type_3          = ::rbr::flag(type_3_mode{});

  struct assume_unitary_option : eve::detail::exact_option<assume_unitary>      {};
  struct extrinsic_option : eve::detail::exact_option<extrinsic>                {};
  struct flat_option : eve::detail::exact_option<flat>                          {};
  struct incomplete_option: eve::detail::exact_option<incomplete>               {};
  struct intrinsic_option : eve::detail::exact_option<intrinsic>                {};
  struct kind_1_option : eve::detail::exact_option<kind_1>                      {};
  struct kind_2_option : eve::detail::exact_option<kind_2>                      {};
  struct regularized_option : eve::detail::exact_option<regularized>            {};
  struct type_1_option : eve::detail::exact_option<type_1>                      {};
  struct type_2_option : eve::detail::exact_option<type_2>                      {};
  struct type_3_option : eve::detail::exact_option<type_3>                      {};


}
