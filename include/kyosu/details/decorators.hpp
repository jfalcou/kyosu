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
  struct regularized_mode       {};
  struct type_1_mode            {};
  struct type_2_mode            {};
  struct type_3_mode            {};

  [[maybe_unused]] inline constexpr auto assume_unitary  = ::rbr::flag(assume_unitary_mode{});
  [[maybe_unused]] inline constexpr auto intrinsic       = ::rbr::flag(intrinsic_mode{});
  [[maybe_unused]] inline constexpr auto extrinsic       = ::rbr::flag(extrinsic_mode{});
  [[maybe_unused]] inline constexpr auto flat            = ::rbr::flag(flat_mode{});
  [[maybe_unused]] inline constexpr auto incomplete      = ::rbr::flag(incomplete_mode{});
  [[maybe_unused]] inline constexpr auto regularized     = ::rbr::flag(regularized_mode{});
  [[maybe_unused]] inline constexpr auto type_1          = ::rbr::flag(type_1_mode{});
  [[maybe_unused]] inline constexpr auto type_2          = ::rbr::flag(type_2_mode{});
  [[maybe_unused]] inline constexpr auto type_3          = ::rbr::flag(type_3_mode{});

  struct assume_unitary_option : eve::detail::exact_option<assume_unitary>      {};
  struct extrinsic_option : eve::detail::exact_option<extrinsic>                {};
  struct flat_option : eve::detail::exact_option<flat>                          {};
  struct incomplete_option: eve::detail::exact_option<incomplete>               {};
  struct intrinsic_option : eve::detail::exact_option<intrinsic>                {};
  struct regularized_option : eve::detail::exact_option<regularized>            {};
  struct type_1_option : eve::detail::exact_option<type_1>                      {};
  struct type_2_option : eve::detail::exact_option<type_2>                      {};
  struct type_3_option : eve::detail::exact_option<type_3>                      {};

  //putting eve decorators in kyosu namespace

//   [[maybe_unused]] inline constexpr auto almost         = ::rbr::flag(eve::almost_mode{})         ;
//   [[maybe_unused]] inline constexpr auto associated     = ::rbr::flag(eve::associated_mode{})     ;
//   [[maybe_unused]] inline constexpr auto compensated    = ::rbr::flag(eve::compensated_mode{})    ;
//   [[maybe_unused]] inline constexpr auto condon_shortley= ::rbr::flag(eve::condon_shortley_mode{});
//   [[maybe_unused]] inline constexpr auto cylindrical    = ::rbr::flag(eve::cylindrical_mode{})    ;
//   [[maybe_unused]] inline constexpr auto definitely     = ::rbr::flag(eve::definitely_mode{})     ;
//   [[maybe_unused]] inline constexpr auto eccentric      = ::rbr::flag(eve::eccentric_mode{})      ;
//   [[maybe_unused]] inline constexpr auto kind_1         = ::rbr::flag(eve::kind_1_mode{})         ;
//   [[maybe_unused]] inline constexpr auto kind_2         = ::rbr::flag(eve::kind_2_mode{})         ;
//   [[maybe_unused]] inline constexpr auto left           = ::rbr::flag(eve::left_mode{})           ;
//   [[maybe_unused]] inline constexpr auto modular        = ::rbr::flag(eve::modular_mode{})        ;
//   [[maybe_unused]] inline constexpr auto numeric        = ::rbr::flag(eve::numeric_mode{})        ;
//   [[maybe_unused]] inline constexpr auto p_kind         = ::rbr::flag(eve::p_kind_mode{})         ;
//   [[maybe_unused]] inline constexpr auto promote        = ::rbr::flag(eve::promote_mode{})        ;
//   [[maybe_unused]] inline constexpr auto q_kind         = ::rbr::flag(eve::q_kind_mode{})         ;
//   [[maybe_unused]] inline constexpr auto right          = ::rbr::flag(eve::right_mode{})          ;
//   [[maybe_unused]] inline constexpr auto spherical      = ::rbr::flag(eve::spherical_mode{})      ;
//   [[maybe_unused]] inline constexpr auto successor      = ::rbr::flag(eve::successor_mode{})      ;
//   [[maybe_unused]] inline constexpr auto threshold      = ::rbr::flag(eve::threshold_mode{})      ;
//   [[maybe_unused]] inline constexpr auto upper          = ::rbr::flag(eve::upper_mode{})          ;
//   [[maybe_unused]] inline constexpr auto lower          = ::rbr::flag(eve::lower_mode{})          ;
//   [[maybe_unused]] inline constexpr auto strict         = ::rbr::flag(eve::strict_mode{})         ;
//   [[maybe_unused]] inline constexpr auto widen          = ::rbr::flag(eve::widen_mode{})          ;
//   [[maybe_unused]] inline constexpr auto to_nearest     = ::rbr::flag(eve::to_nearest_mode{})     ;
//   [[maybe_unused]] inline constexpr auto downward       = ::rbr::flag(eve::downward_mode{})       ;
//   [[maybe_unused]] inline constexpr auto upward         = ::rbr::flag(eve::upward_mode{})         ;
//   [[maybe_unused]] inline constexpr auto toward_zero    = ::rbr::flag(eve::toward_zero_mode{})    ;
//   [[maybe_unused]] inline constexpr auto pedantic       = ::rbr::flag(eve::pedantic_mode{})       ;
//   [[maybe_unused]] inline constexpr auto raw            = ::rbr::flag(eve::raw_mode{})            ;
//   [[maybe_unused]] inline constexpr auto saturated      = ::rbr::flag(eve::saturated_mode{})      ;

//   struct almost_option             : eve::detail::exact_option<eve::almost>         {};
//   struct associated_option         : eve::detail::exact_option<eve::associated>     {};
//   struct compensated_option        : eve::detail::exact_option<eve::compensated>    {};
//   struct condon_shortley_option    : eve::detail::exact_option<eve::condon_shortley>{};
//   struct cylindrical_option        : eve::detail::exact_option<eve::cylindrical>    {};
//   struct definitely_option         : eve::detail::exact_option<eve::definitely>     {};
//   struct eccentric_option          : eve::detail::exact_option<eve::eccentric>      {};
//   struct kind_1_option             : eve::detail::exact_option<eve::kind_1>         {};
//   struct kind_2_option             : eve::detail::exact_option<eve::kind_2>         {};
//   struct left_option               : eve::detail::exact_option<eve::left>           {};
//   struct modular_option            : eve::detail::exact_option<eve::modular>        {};
//   struct numeric_option            : eve::detail::exact_option<eve::numeric>        {};
//   struct p_kind_option             : eve::detail::exact_option<eve::p_kind>         {};
//   struct promote_option            : eve::detail::exact_option<eve::promote>        {};
//   struct q_kind_option             : eve::detail::exact_option<eve::q_kind>         {};
//   struct right_option              : eve::detail::exact_option<eve::right>          {};
//   struct spherical_option          : eve::detail::exact_option<eve::spherical>      {};
//   struct successor_option          : eve::detail::exact_option<eve::successor>      {};
//   struct threshold_option          : eve::detail::exact_option<eve::threshold>      {};
//   struct upper_option              : eve::detail::exact_option<eve::upper>          {};
//   struct lower_option              : eve::detail::exact_option<eve::lower>          {};
//   struct strict_option             : eve::detail::exact_option<eve::strict>         {};
//   struct widen_option              : eve::detail::exact_option<eve::widen>          {};
//   struct to_nearest_option         : eve::detail::exact_option<eve::to_nearest>     {};
//   struct downward_option           : eve::detail::exact_option<eve::downward>       {};
//   struct upward_option             : eve::detail::exact_option<eve::upward>         {};
//   struct toward_zero_option        : eve::detail::exact_option<eve::toward_zero>    {};
//   struct pedantic_option           : eve::detail::exact_option<eve::pedantic>       {};
//   struct raw_option                : eve::detail::exact_option<eve::raw>            {};
//   struct saturated_option          : eve::detail::exact_option<eve::saturated>      {};
 using eve::kind_2_option;

 using eve::almost;
 using eve::associated;
 using eve::compensated;
 using eve::condon_shortley;
 using eve::cylindrical;
 using eve::definitely;
 using eve::eccentric;
 using eve::kind_1;
 using eve::kind_2;
 using eve::left;
 using eve::modular;
 using eve::numeric;
 using eve::p_kind;
 using eve::promote;
 using eve::q_kind;
 using eve::right;
 using eve::spherical;
 using eve::successor;
 using eve::threshold;
 using eve::upper;
 using eve::lower;
 using eve::strict;
 using eve::widen;
 using eve::to_nearest;
 using eve::downward;
 using eve::upward;
 using eve::toward_zero;
 using eve::pedantic;
 using eve::raw;
 using eve::saturated;
 }
