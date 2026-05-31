//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check polarpi scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(0, +10),
              tts::randoms(-1, +1))
  <typename T>(T const& a0, T const& a1)
{

  using eve::radpi;
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto [ra, ia] = kyosu::from_polarpi(a0[i], a1[i]);
    TTS_ULP_EQUAL(ra, a0[i]*eve::cos[radpi](a1[i]), 0.5);
    TTS_ULP_EQUAL(ia, a0[i]*eve::sin[radpi](a1[i]), 0.5);
   }
};
TTS_CASE_WITH("Check polarpi simd",
              tts::bunch<kyosu::simd_real_types>,
              tts::randoms(0, +10),
              tts::randoms(-1, +1))
  <typename T>(T const& a0, T const& a1)
{

  using eve::radpi;
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto [ra, ia] = kyosu::from_polarpi(a0[i], a1[i]);
    TTS_ULP_EQUAL(ra, a0[i]*eve::cos[radpi](a1[i]), 0.5);
    TTS_ULP_EQUAL(ia, a0[i]*eve::sin[radpi](a1[i]), 0.5);
   }
};
