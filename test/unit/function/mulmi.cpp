//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::mulmi over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T data)
{
  TTS_EQUAL(kyosu::mulmi(data), kyosu::mi(kyosu::as<T>()) * data);
};

TTS_CASE_WITH("Check kyosu::mulmi over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T r, T i)
{
  TTS_EQUAL(kyosu::mulmi(kyosu::complex(r, i)), kyosu::mi(kyosu::as<T>()) * kyosu::complex(r, i));
};

TTS_CASE_WITH("Check kyosu::mulmi over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::mulmi(type(r, i, j, k)), kyosu::mi(kyosu::as<T>()) * type(r, i, j, k));
};

TTS_CASE_WITH("Check kyosu::mulmi over octonion",
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
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::mulmi(type(r, i, j, k, l, li, lj, lk)), kyosu::mi(kyosu::as<T>()) * type(r, i, j, k, l, li, lj, lk));
};
