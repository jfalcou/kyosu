//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_not_finite over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_not_finite(data), eve::is_not_finite(data));
};

TTS_CASE_WITH ( "Check kyosu::is_not_finite over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_not_finite(kyosu::complex(r,i)), eve::is_not_finite(r) || eve::is_not_finite(i));
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_finite(z), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_finite over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_finite(type(r,i,j,k)), eve::is_not_finite(r) || eve::is_not_finite(i) || eve::is_not_finite(j) || eve::is_not_finite(k));
  TTS_EQUAL(kyosu::is_not_finite(z), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_finite over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  auto z(eve::inf(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_finite(type(r,i,j,k,l,li,lj,lk)), eve::is_not_finite(r) || eve::is_not_finite(i) || eve::is_not_finite(j) || eve::is_not_finite(k)
            || eve::is_not_finite(l) || eve::is_not_finite(li) || eve::is_not_finite(lj) || eve::is_not_finite(lk) );
  TTS_EQUAL(kyosu::is_not_finite(z), eve::true_(eve::as(r)));
};
