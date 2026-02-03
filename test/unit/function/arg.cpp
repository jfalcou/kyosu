//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::arg over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_ULP_EQUAL(kyosu::arg(data), eve::arg(data), 0.5);
};

TTS_CASE_WITH("Check kyosu::arg over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_ULP_EQUAL(kyosu::arg(kyosu::complex(r, i)), eve::atan2[eve::pedantic](i, r), 0.5);
};
