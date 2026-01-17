//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::conj over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::conj(data), data);
};

TTS_CASE_WITH("Check kyosu::conj over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_EQUAL(kyosu::conj(kyosu::complex(r, i)), kyosu::complex(r, -i));
  TTS_IEEE_EQUAL(kyosu::conj(kyosu::complex(eve::nan(eve::as(r)), i)), kyosu::complex(eve::nan(eve::as(r)), -i));
  TTS_IEEE_EQUAL(kyosu::conj(kyosu::complex(r, eve::nan(eve::as(i)))), kyosu::complex(r, eve::nan(eve::as(i))));
};

TTS_CASE_WITH("Check kyosu::conj over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
(auto r, auto i, auto j, auto k)
{
  TTS_EQUAL(kyosu::conj(kyosu::quaternion(r, i, j, k)), kyosu::quaternion(r, -i, -j, -k));
};

TTS_CASE_WITH("Check kyosu::conj over octonion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  auto o = kyosu::octonion_t<T>(r, i, j, k, l, li, lj, lk);
  TTS_EQUAL(kyosu::conj(o), kyosu::octonion_t<T>(r, -i, -j, -k, -l, -li, -lj, -lk));
};
