//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sqr over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::sqr(data), eve::sqr(data), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::sqr over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  auto c = kyosu::complex(r,i);
  TTS_RELATIVE_EQUAL(kyosu::sqr(c), c*c, 1e-7);
};

TTS_CASE_WITH ( "Check kyosu::sqr over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto q = type(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::sqr(q), q*q, 1e-6);
};
