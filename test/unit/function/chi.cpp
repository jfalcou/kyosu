//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::chi over real", kyosu::real_types, tts::randoms(-10, 10))
<typename T>(T data)
{
  auto b = [](auto z) { return kyosu::abs(z) < 4; };
  TTS_RELATIVE_EQUAL(kyosu::chi(data, b), eve::chi(data, b), tts::prec<T>());
};

TTS_CASE_WITH("Check kyosu::chi over complex", kyosu::real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T a0, T a1)
{
  auto b = [](auto z) { return kyosu::abs(z) < 5; };
  kyosu::complex_t<T> data(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::chi(data, b), kyosu::complex(eve::chi(kyosu::abs(data), b)), tts::prec<T>());
  auto r = kyosu::if_else(kyosu::real(data) < 3, kyosu::chi(data, b), data);
  TTS_RELATIVE_EQUAL(kyosu::chi[kyosu::real(data) < 3](data, b), r, tts::prec<T>());
};
