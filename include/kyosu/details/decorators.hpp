//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/detail/raberu.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace kyosu
{
  struct assume_unitary_mode
  {
  };
  struct extrinsic_mode
  {
  };
  struct flat_mode
  {
  };
  struct incomplete_mode
  {
  };
  struct intrinsic_mode
  {
  };
  struct real_only_mode
  {
  };
  struct regularized_mode
  {
  };
  struct type_1_mode
  {
  };
  struct type_2_mode
  {
  };
  struct type_3_mode
  {
  };
  struct landau_mode
  {
  };
  struct riemann_mode
  {
  };

  [[maybe_unused]] inline constexpr auto assume_unitary = ::rbr::flag(assume_unitary_mode{});
  [[maybe_unused]] inline constexpr auto intrinsic = ::rbr::flag(intrinsic_mode{});
  [[maybe_unused]] inline constexpr auto extrinsic = ::rbr::flag(extrinsic_mode{});
  [[maybe_unused]] inline constexpr auto flat = ::rbr::flag(flat_mode{});
  [[maybe_unused]] inline constexpr auto incomplete = ::rbr::flag(incomplete_mode{});
  [[maybe_unused]] inline constexpr auto real_only = ::rbr::flag(real_only_mode{});
  [[maybe_unused]] inline constexpr auto regularized = ::rbr::flag(regularized_mode{});
  [[maybe_unused]] inline constexpr auto type_1 = ::rbr::flag(type_1_mode{});
  [[maybe_unused]] inline constexpr auto type_2 = ::rbr::flag(type_2_mode{});
  [[maybe_unused]] inline constexpr auto type_3 = ::rbr::flag(type_3_mode{});
  [[maybe_unused]] inline constexpr auto riemann = ::rbr::flag(riemann_mode{});
  [[maybe_unused]] inline constexpr auto landau = ::rbr::flag(landau_mode{});

  struct assume_unitary_option : eve::detail::exact_option<assume_unitary>
  {
  };
  struct extrinsic_option : eve::detail::exact_option<extrinsic>
  {
  };
  struct flat_option : eve::detail::exact_option<flat>
  {
  };
  struct incomplete_option : eve::detail::exact_option<incomplete>
  {
  };
  struct intrinsic_option : eve::detail::exact_option<intrinsic>
  {
  };
  struct real_only_option : eve::detail::exact_option<real_only>
  {
  };
  struct regularized_option : eve::detail::exact_option<regularized>
  {
  };
  struct type_1_option : eve::detail::exact_option<type_1>
  {
  };
  struct type_2_option : eve::detail::exact_option<type_2>
  {
  };
  struct type_3_option : eve::detail::exact_option<type_3>
  {
  };
  struct riemann_option : eve::detail::exact_option<riemann>
  {
  };
  struct landau_option : eve::detail::exact_option<landau>
  {
  };

  //putting eve decorators in kyosu namespace

  using eve::almost_option;
  using eve::associated_option;
  using eve::compensated_option;
  using eve::condon_shortley_option;
  using eve::cylindrical_option;
  using eve::definitely_option;
  using eve::downward_option;
  using eve::eccentric_option;
  using eve::kind_1_option;
  using eve::kind_2_option;
  using eve::left_option;
  using eve::lower_option;
  using eve::modular_option;
  using eve::numeric_option;
  using eve::p_kind_option;
  using eve::pedantic_option;
  using eve::promote_option;
  using eve::q_kind_option;
  using eve::raw_option;
  using eve::right_option;
  using eve::saturated_option;
  using eve::spherical_option;
  using eve::strict_option;
  using eve::successor_option;
  using eve::threshold_option;
  using eve::to_nearest_option;
  using eve::toward_zero_option;
  using eve::upper_option;
  using eve::upward_option;
  using eve::widen_option;

  using eve::rad_option;
  using eve::radpi_option;

  using eve::almost;
  using eve::associated;
  using eve::compensated;
  using eve::condon_shortley;
  using eve::cylindrical;
  using eve::definitely;
  using eve::downward;
  using eve::eccentric;
  using eve::kind_1;
  using eve::kind_2;
  using eve::left;
  using eve::lower;
  using eve::modular;
  using eve::numeric;
  using eve::p_kind;
  using eve::pedantic;
  using eve::promote;
  using eve::q_kind;
  using eve::raw;
  using eve::right;
  using eve::saturated;
  using eve::spherical;
  using eve::strict;
  using eve::successor;
  using eve::threshold;
  using eve::to_nearest;
  using eve::toward_zero;
  using eve::upper;
  using eve::upward;
  using eve::widen;

  using eve::rad;
  using eve::radpi;
}
