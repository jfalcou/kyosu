//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_not_infinite over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_not_infinite(data), eve::is_not_infinite(data));
};

TTS_CASE_WITH ( "Check kyosu::is_not_infinite over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_not_infinite(kyosu::complex(r,i)), eve::is_not_infinite(r) && eve::is_not_infinite(i));
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_infinite(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_infinite over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_infinite(type(r,i,j,k)), eve::is_not_infinite(r) && eve::is_not_infinite(i) && eve::is_not_infinite(j) && eve::is_not_infinite(k));
  TTS_EQUAL(kyosu::is_not_infinite(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_infinite over octonion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_infinite(type(r,i,j,k,l,li,lj,lk)), eve::is_not_infinite(r) && eve::is_not_infinite(i) && eve::is_not_infinite(j) && eve::is_not_infinite(k)
            && eve::is_not_infinite(l) && eve::is_not_infinite(li) && eve::is_not_infinite(lj) && eve::is_not_infinite(lk) );
  TTS_EQUAL(kyosu::is_not_infinite(z), eve::false_(eve::as(r)));
};
