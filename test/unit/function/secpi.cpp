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
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  using u_t  = eve::underlying_type_t<T>;
  auto pi = eve::pi(eve::as<u_t>());
  auto q = ke_t(r,i,j,k);
  TTS_RELATIVE_EQUAL(kyosu::secpi(q), kyosu::sec(pi*q), 1e-5);
};
