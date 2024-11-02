//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::oneminus over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::oneminus(data), eve::oneminus(data));
};

TTS_CASE_WITH ( "Check kyosu::oneminus over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>(T r, T i)
{
  using type = kyosu::complex_t<T>;
  auto o = type(1);
  TTS_EQUAL(kyosu::oneminus(type(r,i)), o-type(r,i));
};

TTS_CASE_WITH ( "Check kyosu::oneminus over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-5,5), tts::randoms(-5,5)
                              , tts::randoms(-5,5), tts::randoms(-5,5)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto o = type(T(1));
  TTS_EQUAL(kyosu::oneminus(type(r,i,j,k)), o-type(r,i,j,k));
};
