//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_real over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::is_real(data), eve::is_real(data));
};

TTS_CASE_WITH ( "Check kyosu::is_real over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  TTS_EQUAL(kyosu::is_real(kyosu::complex(r,i)), eve::is_eqz(i));
  TTS_EQUAL(kyosu::is_real(kyosu::complex(r,eve::zero(eve::as(r)))), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_real over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  TTS_EQUAL(kyosu::is_real(type(r,i,j,k)), eve::is_eqz(i) && eve::is_eqz(j) && eve::is_eqz(k));
  TTS_EQUAL(kyosu::is_real(type(r)), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_real over octonion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  TTS_EQUAL(kyosu::is_real(type(r,i,j,k,l,li,lj,lk)),  eve::is_eqz(i) && eve::is_eqz(j) && eve::is_eqz(k)
            && eve::is_eqz(l) && eve::is_eqz(li) && eve::is_eqz(lj) && eve::is_eqz(lk) );
  TTS_EQUAL(kyosu::is_real(type(r)), eve::true_(eve::as(r)));
};
