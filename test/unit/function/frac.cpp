//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::frac over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_EQUAL(kyosu::frac(data), eve::frac(data));
};

TTS_CASE_WITH("Check kyosu::frac over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_EQUAL(kyosu::frac(kyosu::complex(r, i)), kyosu::complex(eve::frac(r), eve::frac(i)));
};

TTS_CASE_WITH("Check kyosu::frac over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::frac(type(r, i, j, k)), type(eve::frac(r), eve::frac(i), eve::frac(j), eve::frac(k)));
};

TTS_CASE_WITH("Check kyosu::frac over octonion",
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
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::frac(type(r, i, j, k, l, li, lj, lk)),
            type(eve::frac(r), eve::frac(i), eve::frac(j), eve::frac(k), eve::frac(l), eve::frac(li), eve::frac(lj),
                 eve::frac(lk)));
};
