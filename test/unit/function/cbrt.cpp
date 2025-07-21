//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cbrt over real"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>  (T v)
{
  auto kr = kyosu::cbrt(v, 2);
  TTS_RELATIVE_EQUAL(kyosu::pow(kr, 3), kyosu::complex(v), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::cbrt over complex"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
(auto r, auto i)
{
  using T =  decltype(r);
  auto c = kyosu::complex(r,i);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::cbrt(c), 3), c, tts::prec<T>());
};
