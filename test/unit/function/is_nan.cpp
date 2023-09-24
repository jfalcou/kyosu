//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_nan over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_nan(data), eve::is_nan(data));
};

TTS_CASE_WITH ( "Check kyosu::is_nan over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_nan(kyosu::complex(r,i)), eve::is_nan(r) || eve::is_nan(i));
  auto z(eve::nan(eve::as(r)));
  TTS_EQUAL(kyosu::is_nan(z), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_nan over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(eve::nan(eve::as(r)));
  TTS_EQUAL(kyosu::is_nan(type(r,i,j,k)), eve::is_nan(r) || eve::is_nan(i) || eve::is_nan(j) || eve::is_nan(k));
  TTS_EQUAL(kyosu::is_nan(z), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_nan over octonion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  auto z(eve::nan(eve::as(r)));
  TTS_EQUAL(kyosu::is_nan(type(r,i,j,k,l,li,lj,lk)), eve::is_nan(r) || eve::is_nan(i) || eve::is_nan(j) || eve::is_nan(k)
            || eve::is_nan(l) || eve::is_nan(li) || eve::is_nan(lj) || eve::is_nan(lk) );
  TTS_EQUAL(kyosu::is_nan(z), eve::true_(eve::as(r)));
};
