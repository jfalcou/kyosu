//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_finite over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_finite(data), eve::is_finite(data));
};

TTS_CASE_WITH ( "Check kyosu::is_finite over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_finite(kyosu::to_complex(r,i)), eve::is_finite(r) && eve::is_finite(i));
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_finite(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_finite over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::as_quaternion_t<T>;
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_finite(type(r,i,j,k)), eve::is_finite(r) && eve::is_finite(i) && eve::is_finite(j) && eve::is_finite(k));
  TTS_EQUAL(kyosu::is_finite(z), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_finite over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::as_octonion_t<T>;
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_finite(type(r,i,j,k,l,li,lj,lk)), eve::is_finite(r) && eve::is_finite(i) && eve::is_finite(j) && eve::is_finite(k)
            && eve::is_finite(l) && eve::is_finite(li) && eve::is_finite(lj) && eve::is_finite(lk) );
  TTS_EQUAL(kyosu::is_finite(z), eve::false_(eve::as(r)));
};
