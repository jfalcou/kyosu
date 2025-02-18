//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::rec over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::rec(data), eve::rec(data), 0.5);
};


TTS_CASE_WITH ( "Check kyosu::rec over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  auto o = eve::one(eve::as(eve::underlying_type_t<T>()));
  using ke_t = kyosu::quaternion_t<T>;
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::rec(q), o/q, tts::prec<T>());
};
