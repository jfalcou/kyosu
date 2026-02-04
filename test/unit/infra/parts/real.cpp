//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include "kyosu/types/octonion.hpp"
#include "tts/tools/typename.hpp"
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::real over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T data)
{
  using real_t = kyosu::as_real_type_t<T>;
  TTS_EQUAL(kyosu::real(data), data);

  kyosu::real(data) = real_t{7.5};
  TTS_EQUAL(kyosu::real(data), real_t{7.5});
};

TTS_CASE_WITH("Check kyosu::real over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  auto data = kyosu::complex(r, i);
  TTS_EQUAL(kyosu::real(data), r);

  kyosu::real(data) = i;
  TTS_EQUAL(kyosu::real(data), i);
};

TTS_CASE_WITH("Check kyosu::real over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
(auto r, auto i, auto j, auto k)
{
  auto data = kyosu::quaternion(r, i, j, k);
  TTS_EQUAL(kyosu::real(data), r);

  kyosu::real(data) = i;
  TTS_EQUAL(kyosu::real(data), i);
};

TTS_CASE_WITH("Check kyosu::real over octonion",
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
  auto data = kyosu::octonion_t<T>(r, i, j, k, l, li, lj, lk);
  TTS_EQUAL(kyosu::real(data), r);

  kyosu::real(data) = i;
  TTS_EQUAL(kyosu::real(data), i);
};
