//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::agd over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-1,1))
              )
<typename T>(T data)
{
  TTS_RELATIVE_EQUAL(kyosu::agd(data), kyosu::complex(eve::agd(data)), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::agd over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-1,1), tts::randoms(-1,1))
              )
<typename T>(T a0, T a1)
{
  kyosu::complex_t<T> data(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::gd( kyosu::agd(data)), data,  tts::prec<T>(3.e-3, 1.e-6));
};
