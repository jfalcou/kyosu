//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::pure over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::pure(data), eve::zero(eve::as(data)));
};

TTS_CASE_WITH ( "Check kyosu::pure over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
  <typename T>(T r, T i)
{
  TTS_EQUAL(kyosu::pure(kyosu::complex(r,i)), kyosu::complex(T(0),i));
};

TTS_CASE_WITH ( "Check kyosu::pure over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::pure(type(r,i,j,k)), type(T(0), i, j, k));
};

TTS_CASE_WITH ( "Check kyosu::pure over octonion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::pure(type(r,i,j,k,l,li,lj,lk)), type(T(0),i,j,k,l,li,lj,lk) );
};
