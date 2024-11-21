//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_not_real over not_real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_not_real(data), eve::false_((eve::as(data))));
};

TTS_CASE_WITH ( "Check kyosu::is_not_real over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_not_real(kyosu::complex(r,i)), eve::is_nez(i));
  TTS_EQUAL(kyosu::is_not_real(kyosu::complex(r,eve::zero(eve::as(r)))), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_real over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::is_not_real(type(r,i,j,k)), eve::is_nez(i) || eve::is_nez(j) || eve::is_nez(k));
  TTS_EQUAL(kyosu::is_not_real(type(r)), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_real over octonion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::is_not_real(type(r,i,j,k,l,li,lj,lk)),  eve::is_nez(i) || eve::is_nez(j) || eve::is_nez(k)
            || eve::is_nez(l) || eve::is_nez(li) || eve::is_nez(lj) || eve::is_nez(lk) );
  TTS_EQUAL(kyosu::is_not_real(type(r)), eve::false_(eve::as(r)));
};
