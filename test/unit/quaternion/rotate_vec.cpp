//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check behavior of rotate_vec on wide",
              kyosu::real_types,
              tts::randoms(0.25, +0.75),
              tts::randoms(0.25, +0.75),
              tts::randoms(0.25, +0.75),
              tts::randoms(0.25, +0.75))<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  std::array<T, 3> v{a0, a1, a2};
  auto rsq3 = eve::rec(eve::sqrt_3(eve::as(a3)));
  std::array<T, 3> axis{rsq3, rsq3, rsq3};
  auto q = kyosu::from_angle_axis(eve::pi(eve::as(a0)), std::span<T, 3>(axis));
  auto vr = kyosu::rotate_vec(q, std::span<T, 3>(v));
  auto vr2 = kyosu::rotate_vec(q, std::span<T, 3>(vr));
  TTS_RELATIVE_EQUAL(v[0], vr2[0], 1.0e-4);
};
