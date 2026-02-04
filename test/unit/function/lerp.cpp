//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH(
  "Check kyosu::lerp over real", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10), tts::randoms(0, 1)

)
(auto r0, auto r1, auto t)
{
  TTS_EQUAL(kyosu::lerp(r0, r1, t), eve::lerp(r0, r1, t));
};

TTS_CASE_WITH("Check kyosu::lerp over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(0, 1)

)
(auto r0, auto i0, auto r1, auto i1, auto t)
{
  using T = decltype(r0);
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  TTS_RELATIVE_EQUAL(kyosu::lerp(c0, c1, t), c0 + t * (c1 - c0), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::lerp over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(0, 1)

)
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1, auto t)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0, i0, j0, k0);
  auto q1 = type(r1, i1, j1, k1);
  TTS_RELATIVE_EQUAL(kyosu::lerp(q0, q1, t), q0 + t * (q1 - q0), tts::prec<T>());
};
