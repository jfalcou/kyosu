//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::secpi over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-1, 1), tts::randoms(-1,1)
                              , tts::randoms(-1,1), tts::randoms(-1,1)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::secpi(q), kyosu::rec(kyosu::cospi(q)),tts::prec<T>());

};
