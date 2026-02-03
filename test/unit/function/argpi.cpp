//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::argpi over real", kyosu::real_types, tts::randoms(-10, 10))
(auto data)
{
  TTS_ULP_EQUAL(kyosu::argpi(data), eve::if_else(eve::is_negative(data), eve::one(eve::as(data)), eve::zero), 0.5);
};

TTS_CASE_WITH("Check kyosu::argpi over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
(auto r, auto i)
{
  TTS_ULP_EQUAL(kyosu::argpi(kyosu::complex(r, i)), eve::atan2pi[eve::pedantic](i, r), 0.5);
};
