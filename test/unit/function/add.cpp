//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::add over real", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10)

)
<typename T>(T r0, T r1)
{
  TTS_EQUAL(kyosu::add(r0), r0);
  TTS_RELATIVE_EQUAL(kyosu::add(r0, r1), eve::add(r0, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add(r0, r1, r1), eve::add(r0, r1, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[eve::kahan](r0, r1, r1), eve::add(r0, r1, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add(kumi::tuple{r0, r1, r1}), eve::add(r0, r1, r1), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::add over complex",
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
  TTS_EQUAL(kyosu::add(c0), c0);
  TTS_RELATIVE_EQUAL(kyosu::add(c0, c1), (c0 + c1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add(c0, c1, r1), (c0 + c1 + r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[eve::kahan](c0, c1, r1), kyosu::add(c0, c1, r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add(r0, c1, r1), (r0 + c1 + r1), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[r0 > 0](c0, c1, r1), kyosu::if_else(r0 > 0, (c0 + c1 + r1), c0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[r0 > 0](r0, c1, r1), kyosu::if_else(r0 > 0, (r0 + c1 + r1), kyosu::complex(r0)),
                     tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[r0 > 0](kumi::tuple{r0, c1, r1}),
                     kyosu::if_else(r0 > 0, (r0 + c1 + r1), kyosu::complex(r0)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[r0 > 0](kumi::tuple{c0, c1, r1}), kyosu::if_else(r0 > 0, (c0 + c1 + r1), c0),
                     tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::add over quaternion",
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
  TTS_RELATIVE_EQUAL(kyosu::add(q0, q1), (q0 + q1), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::add(q0, q1, r0), (q0 + q1 + r0), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::add(kumi::tuple{q0, q1, r0}), (q0 + q1 + r0), 1e-7);
  TTS_RELATIVE_EQUAL(kyosu::add[eve::kahan](q0, q1, r0), kyosu::add(q0, q1, r0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[r0 > 0](q0, q1, r0), kyosu::if_else(r0 > 0, (q0 + q1 + r0), q0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::add[r0 > 0](r0, q1, r0), kyosu::if_else(r0 > 0, (r0 + q1 + r0), kyosu::complex(r0)),
                     tts::prec<T>());
};
