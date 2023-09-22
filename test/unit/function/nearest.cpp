//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::nearest over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::nearest(data), eve::nearest(data));
};

TTS_CASE_WITH ( "Check kyosu::nearest over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::nearest(kyosu::complex(r,i)), kyosu::complex(eve::nearest(r),eve::nearest(i)));
};

TTS_CASE_WITH ( "Check kyosu::nearest over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::nearest(type(r,i,j,k)), type(eve::nearest(r), eve::nearest(i), eve::nearest(j), eve::nearest(k)));
};

TTS_CASE_WITH ( "Check kyosu::nearest over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::nearest(type(r,i,j,k,l,li,lj,lk)), type(eve::nearest(r), eve::nearest(i), eve::nearest(j), eve::nearest(k)
                                                       , eve::nearest(l), eve::nearest(li), eve::nearest(lj), eve::nearest(lk) ));
};
