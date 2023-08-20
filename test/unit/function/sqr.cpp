//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sqr over real"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10))
              )
(auto data)
{
  TTS_EQUAL(kyosu::sqr(data), eve::sqr(data));
};

TTS_CASE_WITH ( "Check kyosu::sqr over complex"
              , kyosu::real_types
              , tts::generate(tts::between(-10,10), tts::between(-10,10))
              )
(auto r, auto i)
{
  auto c = kyosu::to_complex(r,i);
  TTS_EQUAL(kyosu::sqr(c), c*c);
};

TTS_CASE_WITH ( "Check kyosu::sqr over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using type = kyosu::as_quaternion_t<T>;
  auto o = type(r,i,j,k);

  TTS_EQUAL(kyosu::sqr(o), o*o);
};
