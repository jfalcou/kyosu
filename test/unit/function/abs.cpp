//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::abs over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::abs(data), eve::abs(data), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::abs over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  TTS_ULP_EQUAL(kyosu::abs(kyosu::complex(r,i)), eve::hypot(r, i), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::abs over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
(auto r, auto i, auto j, auto k)
{
  TTS_ULP_EQUAL(kyosu::abs(kyosu::quaternion(r,i,j,k)), eve::hypot(r, i, j, k), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::abs over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  TTS_ULP_EQUAL(kyosu::abs(kyosu::octonion_t<T>(r,i,j,k,l,li,lj,lk)), eve::hypot(r, i, j, k, l, li, lj, lk), 0.5);
};
