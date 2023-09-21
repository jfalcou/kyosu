//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::floor over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::floor(data), eve::floor(data));
};

TTS_CASE_WITH ( "Check kyosu::floor over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::floor(kyosu::to_complex(r,i)), kyosu::to_complex(eve::floor(r),eve::floor(i)));
};

TTS_CASE_WITH ( "Check kyosu::floor over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::floor(type(r,i,j,k)), type(eve::floor(r), eve::floor(i), eve::floor(j), eve::floor(k)));
};

TTS_CASE_WITH ( "Check kyosu::floor over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::as_octonion_t<T>;
  TTS_EQUAL(kyosu::floor(type(r,i,j,k,l,li,lj,lk)), type(eve::floor(r), eve::floor(i), eve::floor(j), eve::floor(k)
                                                       , eve::floor(l), eve::floor(li), eve::floor(lj), eve::floor(lk) ));
};
