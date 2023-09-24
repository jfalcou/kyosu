//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::expm1 over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(kyosu::expm1(data), eve::expm1(data), 0.5);
};

TTS_CASE_WITH ( "Check kyosu::expm1 over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::expm1(q), kyosu::dec(kyosu::exp(q)), 1e-5);
};
