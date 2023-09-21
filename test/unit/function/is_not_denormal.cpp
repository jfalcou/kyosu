//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_not_denormal over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_not_denormal(data), eve::is_not_denormal(data));
};

TTS_CASE_WITH ( "Check kyosu::is_not_denormal over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_not_denormal(kyosu::to_complex(r,i)), eve::is_not_denormal(r) && eve::is_not_denormal(i));
  auto z(eve::mindenormal(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_denormal(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_denormal over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(eve::mindenormal(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_denormal(type(r,i,j,k)), eve::is_not_denormal(r) && eve::is_not_denormal(i) && eve::is_not_denormal(j) && eve::is_not_denormal(k));
  TTS_EQUAL(kyosu::is_not_denormal(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_denormal over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::as_octonion_t<T>;
  auto z(eve::mindenormal(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_denormal(type(r,i,j,k,l,li,lj,lk)), eve::is_not_denormal(r) && eve::is_not_denormal(i) && eve::is_not_denormal(j) && eve::is_not_denormal(k)
            && eve::is_not_denormal(l) && eve::is_not_denormal(li) && eve::is_not_denormal(lj) && eve::is_not_denormal(lk) );
  TTS_EQUAL(kyosu::is_not_denormal(z), eve::false_(eve::as(r)));
};
