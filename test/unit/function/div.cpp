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
  "Check kyosu::div over real", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10), tts::randoms(-10, 10)

)
<typename T>(T r0, T r1, T r2)
{
  TTS_RELATIVE_EQUAL(kyosu::div(r0, r1), eve::div(r0, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::div(r0, r1, r2), eve::div(r0, r1, r2), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::div(kumi::tuple{r0, r1, r2}), eve::div(r0, r1, r2), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::div over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0, T i0, T r1, T i1)
{
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  TTS_RELATIVE_EQUAL(kyosu::div(c0, c1), (c0 / c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::div(c0, c1, r1), (c0 / (c1 * r1)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::div(r0, c1, r1), (r0 / (c1 * r1)), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::div over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0, i0, j0, k0);
  auto q1 = type(r1, i1, j1, k1);
  TTS_RELATIVE_EQUAL(kyosu::div(q0, q1), (q0 / q1), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::div(q0, q1, r0), (q0 / (q1 * r0)), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::div(kumi::tuple{q0, q1, r0}), (q0 / (q1 * r0)), 1e-7);
};
