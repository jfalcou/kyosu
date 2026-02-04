//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::minabs over real", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10)

)
(auto r0, auto r1)
{
  TTS_EQUAL(kyosu::minabs(r0, r1), eve::minabs(r0, r1));
  TTS_EQUAL(kyosu::minabs(kumi::tuple{r0, r1}), eve::minabs(r0, r1));
  TTS_EQUAL(kyosu::minabs[kyosu::flat](r0, r1), eve::minabs(r0, r1));
  TTS_EQUAL(kyosu::minabs[kyosu::flat](kumi::tuple{r0, r1}), eve::minabs(r0, r1));
};

TTS_CASE_WITH("Check kyosu::minabs over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r0, auto i0, auto r1, auto i1)
{
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  TTS_EQUAL(kyosu::minabs(c0, c1), eve::sqrt(eve::min(kyosu::sqr_abs(c0), kyosu::sqr_abs(c1))));
  TTS_EQUAL(kyosu::minabs(kumi::tuple{c0, c1}), eve::sqrt(eve::min(kyosu::sqr_abs(c0), kyosu::sqr_abs(c1))));
  TTS_EQUAL(kyosu::minabs[eve::numeric](c0, c1), eve::min[eve::numeric](kyosu::abs(c0), kyosu::abs(c1)));
  TTS_EQUAL(kyosu::minabs[eve::numeric](kumi::tuple{c0, c1}), eve::min[eve::numeric](kyosu::abs(c0), kyosu::abs(c1)));
  TTS_EQUAL(kyosu::minabs[kyosu::flat](c0, c1), eve::minabs(r0, i0, r1, i1));
  TTS_EQUAL(kyosu::minabs[kyosu::flat](kumi::tuple{c0, c1}), eve::minabs(r0, i0, r1, i1));
};

TTS_CASE_WITH("Check kyosu::minabs over quaternion",
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
  TTS_EQUAL(kyosu::minabs(q0, q1), eve::sqrt(eve::min(kyosu::sqr_abs(q0), kyosu::sqr_abs(q1))));
  TTS_ULP_EQUAL(kyosu::minabs(kumi::tuple{q0, q1}), eve::sqrt(eve::min(kyosu::sqr_abs(q0), kyosu::sqr_abs(q1))), 0.5);
  TTS_EQUAL(kyosu::minabs[eve::numeric](q0, q1), eve::min[eve::numeric](kyosu::abs(q0), kyosu::abs(q1)));
  TTS_EQUAL(kyosu::minabs[eve::numeric](kumi::tuple{q0, q1}), eve::min[eve::numeric](kyosu::abs(q0), kyosu::abs(q1)));
  TTS_EQUAL(kyosu::minabs[kyosu::flat](q0, q1), eve::minabs(r0, i0, j0, k0, r1, i1, j1, k1));
  TTS_EQUAL(kyosu::minabs[kyosu::flat](kumi::tuple{q0, q1}), eve::minabs(r0, i0, j0, k0, r1, i1, j1, k1));
};
