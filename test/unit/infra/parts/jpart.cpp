//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::jpart over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::jpart(data), eve::zero(eve::as(data)));
};

TTS_CASE_WITH("Check kyosu::jpart over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  auto z = kyosu::complex(r, i);
  TTS_EQUAL(kyosu::jpart(z), eve::zero(eve::as(r)));
};

TTS_CASE_WITH("Check kyosu::jpart over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
(auto r, auto i, auto j, auto k)
{
  auto q = kyosu::quaternion(r, i, j, k);
  TTS_EQUAL(kyosu::jpart(q), j);

  kyosu::jpart(q) = k;
  TTS_EQUAL(kyosu::jpart(q), k);
};

TTS_CASE_WITH("Check kyosu::jpart over octonion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  auto o = kyosu::octonion_t<T>(r, i, j, k, l, li, lj, lk);

  TTS_EQUAL(kyosu::jpart(o), j);

  kyosu::jpart(o) = k;
  TTS_EQUAL(kyosu::jpart(o), k);
};
