//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::sqr_abs over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_ULP_EQUAL(kyosu::sqr_abs(data), eve::sqr(data), 0.5);
};

TTS_CASE_WITH("Check kyosu::sqr_abs over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_ULP_EQUAL(kyosu::sqr_abs(kyosu::complex(r, i)), eve::sqr(eve::hypot[eve::pedantic](r, i)), 1.0);
};

TTS_CASE_WITH("Check kyosu::abs over quaternion",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
(auto r, auto i, auto j, auto k)
{
  TTS_ULP_EQUAL(kyosu::sqr_abs(kyosu::quaternion(r, i, j, k)), eve::sqr(eve::hypot[eve::pedantic](r, i, j, k)), 1.0);
};

TTS_CASE_WITH("Check kyosu::abs over octonion",
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
  TTS_ULP_EQUAL(kyosu::sqr_abs(kyosu::octonion_t<T>(r, i, j, k, l, li, lj, lk)),
                eve::sqr(eve::hypot[eve::pedantic](r, i, j, k, l, li, lj, lk)), 1.0);
};
