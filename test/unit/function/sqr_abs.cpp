//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sqr_abs over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::sqr_abs(data), eve::sqr_abs(data));
};

TTS_CASE_WITH ( "Check kyosu::sqr_abs over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  TTS_ULP_EQUAL(kyosu::sqr_abs(kyosu::complex(r,i)), r*r+i*i, 0.5);
};

TTS_CASE_WITH ( "Check kyosu::sqr_abs over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_ULP_EQUAL(kyosu::sqr_abs(type(r,i,j,k)), r*r+i*i+j*j+k*k, 0.5);
};
