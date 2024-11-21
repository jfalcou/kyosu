//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sinpi over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T r, T i, T j, T k)
{
  using ke_t = kyosu::quaternion_t<T>;
  using u_t  = eve::underlying_type_t<T>;
  auto pi = eve::pi(eve::as<u_t>());
  auto q = ke_t(r,i,j,k);
  if constexpr (sizeof(eve::element_type_t<T>) == 8)
      TTS_RELATIVE_EQUAL(kyosu::sinpi(q/8.0), kyosu::sin(pi*q/8.0), tts::prec<T>());
  else
      TTS_RELATIVE_EQUAL(kyosu::sinpi(q/8.0f), kyosu::sin(pi*q/8.0f), tts::prec<T>());
};
