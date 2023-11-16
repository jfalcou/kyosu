//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::muli over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T data)
{
  TTS_EQUAL(kyosu::muli(data), kyosu::i(kyosu::as<T>())*data);
};

TTS_CASE_WITH ( "Check kyosu::muli over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>(T r, T i)
{
  TTS_EQUAL(kyosu::muli(kyosu::complex(r,i)), kyosu::i(kyosu::as<T>())*kyosu::complex(r,i));
};

TTS_CASE_WITH ( "Check kyosu::muli over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::muli(type(r,i,j,k)), kyosu::i(kyosu::as<T>())*type(r,i,j,k));
};
