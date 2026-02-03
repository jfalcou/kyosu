//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check behavior of from_angle_axis on wide",
              kyosu::real_types,
              tts::randoms(0.5, +1.0),
              tts::randoms(0.5, +1.0),
              tts::randoms(0.5, +1.0),
              tts::randoms(0.5, +1.0))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3){
  {auto q = kyosu::sign(kyosu::quaternion(a0, a1, a2, a3));
auto [a, v] = kyosu::to_angle_axis(q);
std::span<T, 3> vv(v);
auto q1 = kyosu::from_angle_axis(a, vv);
TTS_RELATIVE_EQUAL(q, q1, 1.0e-5);
}
{
  auto c = kyosu::sign(kyosu::complex(a0, a1));
  auto [a, v] = kyosu::to_angle_axis(c);
  std::span<T, 3> vv(v);
  auto c1 = kyosu::from_angle_axis(a, vv);
  TTS_RELATIVE_EQUAL(kyosu::quaternion(c), c1, 1.0e-5);
}

{
  auto [a, v] = kyosu::to_angle_axis(kyosu::sign(a0));
  std::span<T, 3> vv(v);
  auto q1 = kyosu::from_angle_axis(a, vv);
  TTS_RELATIVE_EQUAL(kyosu::quaternion(eve::sign(a0)), q1, 1.0e-5);
}
}
;
