//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check behavior of to_cylindrospherical on wide",
              kyosu::real_types,
              tts::randoms(0.5, +1.0),
              tts::randoms(0.5, +1.0),
              tts::randoms(0.5, +1.0),
              tts::randoms(0.5, +1.0))<typename T>(T const& a0, T const& a1, T const& a2, T const& a3){
  {auto q = kyosu::quaternion(a0, a1, a2, a3);
auto [r1, t1, r2, t2] = kyosu::to_cylindrospherical(q);
auto q1 = kyosu::from_cylindrospherical(r1, t1, r2, t2);
TTS_RELATIVE_EQUAL(q, q1, 1.0e-5);
}
{
  auto c = kyosu::complex(a0, a1);
  auto [r1, t1, r2, t2] = kyosu::to_cylindrospherical(c);
  auto c1 = kyosu::from_cylindrospherical(r1, t1, r2, t2);
  TTS_RELATIVE_EQUAL(kyosu::quaternion(c), c1, 1.0e-5);
}

{
  auto [r1, t1, r2, t2] = kyosu::to_cylindrospherical(a0);
  auto q1 = kyosu::from_cylindrospherical(r1, t1, r2, t2);
  TTS_RELATIVE_EQUAL(kyosu::quaternion(a0), q1, 1.0e-5);
}
}
;
