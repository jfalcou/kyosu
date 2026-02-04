//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>

TTS_CASE_WITH("Check behavior of acoth on scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T const& a0, T const& a1)
{
  for (auto e : a0)
  {
    for (auto f : a1)
    {
      auto z = kyosu::complex(e, f);
      TTS_RELATIVE_EQUAL(kyosu::acoth(z), kyosu::atanh(kyosu::rec(z)), tts::prec<T>());
    }
  }
};

TTS_CASE_WITH("Check behavior of acoth on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  auto z = kyosu::complex(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::acoth(z), kyosu::atanh(kyosu::rec(z)), tts::prec<T>());
};
