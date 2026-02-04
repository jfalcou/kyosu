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
  "Check kyosu::fnma over real", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10), tts::randoms(-10, 10)

)
(auto r0, auto r1, auto r2)
{
  TTS_EQUAL(kyosu::fnma(r0, r1, r2), eve::fnma(r0, r1, r2));
};

TTS_CASE_WITH("Check kyosu::fnma over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r0, auto i0, auto r1, auto i1, auto r2, auto i2)
{
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  auto c2 = kyosu::complex(r2, i2);
  TTS_RELATIVE_EQUAL(kyosu::fnma(c0, c1, c2), -c0 * c1 + c2, 1e-7);
};

TTS_CASE_WITH("Check kyosu::fnma over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1, T r2, T i2, T j2, T k2)
{
  using type = kyosu::quaternion_t<T>;
  auto q0 = type(r0, i0, j0, k0);
  auto q1 = type(r1, i1, j1, k1);
  auto q2 = type(r2, i2, j2, k2);
  TTS_RELATIVE_EQUAL(kyosu::fnma(q0, q1, q2), -q0 * q1 + q2, 1e-7);
};
