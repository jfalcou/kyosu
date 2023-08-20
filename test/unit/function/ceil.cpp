//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::ceil over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::ceil(data), eve::ceil(data));
};

TTS_CASE_WITH ( "Check kyosu::ceil over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::ceil(kyosu::to_complex(r,i)), kyosu::to_complex(eve::ceil(r),eve::ceil(i)));
};

TTS_CASE_WITH ( "Check kyosu::ceil over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::as_quaternion_t<T>;
  TTS_EQUAL(kyosu::ceil(type(r,i,j,k)), type(eve::ceil(r), eve::ceil(i), eve::ceil(j), eve::ceil(k)));
};

TTS_CASE_WITH ( "Check kyosu::ceil over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::as_octonion_t<T>;
  TTS_EQUAL(kyosu::ceil(type(r,i,j,k,l,li,lj,lk)), type(eve::ceil(r), eve::ceil(i), eve::ceil(j), eve::ceil(k)
                                                       , eve::ceil(l), eve::ceil(li), eve::ceil(lj), eve::ceil(lk) ));
};