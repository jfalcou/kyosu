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

TTS_CASE_WITH("Check behavior of acotpi on scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T const& a0, T const& a1)
{
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto z = kyosu::complex(a0[i], a1[i]);
    TTS_RELATIVE_EQUAL(kyosu::acotpi(z), kyosu::atanpi(kyosu::rec(z)), tts::prec<T>());
  }
};

TTS_CASE_WITH("Check behavior of acot on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  auto z = kyosu::complex(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::acotpi(z), kyosu::atanpi(kyosu::rec(z)), tts::prec<T>());
};
