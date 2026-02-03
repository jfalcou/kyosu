//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::dot over real",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r0, auto r1, auto r2, auto r3)
{
  TTS_EQUAL(kyosu::dot(r0, r1), r0 * r1);
  auto d = kyosu::dot(r0, r1, r2, r3);
  TTS_RELATIVE_EQUAL(d, r0 * kyosu::conj(r2) + r1 * kyosu::conj(r3), 1e-7);
  TTS_RELATIVE_EQUAL(d, kyosu::dot(kumi::make_tuple(r0, r1, r2, r3)), 1e-7);
  TTS_RELATIVE_EQUAL(d, kyosu::dot(kumi::make_tuple(r0, r1), kumi::make_tuple(r2, r3)), 1e-7);
};

TTS_CASE_WITH("Check kyosu::dot over complex",
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
  TTS_RELATIVE_EQUAL(kyosu::dot(c0, c1), c0 * kyosu::conj(c1), 1e-7);
  auto c2 = kyosu::complex(r1, i0);
  auto c3 = kyosu::complex(r1, i0);
  auto d = kyosu::dot(c0, c1, c2, c3);
  TTS_RELATIVE_EQUAL(d, c0 * kyosu::conj(c2) + c1 * kyosu::conj(c3), 1e-7);
  TTS_RELATIVE_EQUAL(d, kyosu::dot(kumi::make_tuple(c0, c1, c2, c3)), 1e-7);
  TTS_RELATIVE_EQUAL(d, kyosu::dot(kumi::make_tuple(c0, c1), kumi::make_tuple(c2, c3)), 1e-7);
};

TTS_CASE_WITH("Check kyosu::dot over quaternion",
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
  TTS_RELATIVE_EQUAL(kyosu::dot(q0, q1), q0 * kyosu::conj(q1), 1e-7);
  auto q2 = type(r1, i0, r0, i0);
  auto q3 = type(r1, i0, j0, k1);
  auto d = kyosu::dot(q0, q1, q2, q3);
  TTS_RELATIVE_EQUAL(d, q0 * kyosu::conj(q2) + q1 * kyosu::conj(q3), 1e-7);
  TTS_RELATIVE_EQUAL(d, kyosu::dot(kumi::make_tuple(q0, q1, q2, q3)), 1e-7);
  TTS_RELATIVE_EQUAL(d, kyosu::dot(kumi::make_tuple(q0, q1), kumi::make_tuple(q2, q3)), 1e-7);
};
