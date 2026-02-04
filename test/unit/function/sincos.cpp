//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::sin over quaternion",
              kyosu::simd_real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k){{auto [s, c] = kyosu::sincos(r);
TTS_RELATIVE_EQUAL(s, kyosu::sin(r), tts::prec<T>());
TTS_RELATIVE_EQUAL(c, kyosu::cos(r), tts::prec<T>());
}
{
  using ke_t = kyosu::complex_t<T>;
  auto cq = ke_t(r, i);
  auto [s, c] = kyosu::sincos(cq);
  TTS_RELATIVE_EQUAL(s, kyosu::sin(cq), tts::prec<T>());
  TTS_RELATIVE_EQUAL(c, kyosu::cos(cq), tts::prec<T>());
}
{
  using ke_t = kyosu::quaternion_t<T>;
  auto q = ke_t(r, i, j, k);
  auto [s, c] = kyosu::sincos(q);
  TTS_RELATIVE_EQUAL(s, kyosu::sin(q), tts::prec<T>());
  TTS_RELATIVE_EQUAL(c, kyosu::cos(q), tts::prec<T>());
}
}
;
