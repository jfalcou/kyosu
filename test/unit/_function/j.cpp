//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::j"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
                            , tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>(T r, T i, T j, T k)
{
  using kyosu::as;
  using u_t = eve::underlying_type_t<T>;
  TTS_EQUAL(kyosu::j(as<u_t>()), kyosu::quaternion_t<u_t>(0, 0, 1, 0));
  auto c = kyosu::complex_t<T>(r, i);
  auto z = kyosu::quaternion_t<T>(r, i, j, k);
  TTS_EQUAL(kyosu::j(eve::as_element(c)), kyosu::quaternion_t<u_t>(0, 0, 1, 0));
  TTS_EQUAL(kyosu::j(eve::as_element(z)), kyosu::quaternion_t<u_t>(0, 0, 1, 0));
};
