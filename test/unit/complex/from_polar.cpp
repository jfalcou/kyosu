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


TTS_CASE_WITH("Check from_polar scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(0, +10),
              tts::randoms(-4, +4))
  <typename T>(T const& a0, T const& a1)
{

  using eve::rad;
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto [ra, ia] = kyosu::from_polar(a0[i], a1[i]);
    TTS_ULP_EQUAL(ra, a0[i]*eve::cos(a1[i]), 0.5);
    TTS_ULP_EQUAL(ia, a0[i]*eve::sin(a1[i]), 0.5);
    auto c = std::polar(a0[i], a1[i]);
    TTS_ULP_EQUAL(ra, std::real(c), 0.5);
    TTS_ULP_EQUAL(ia, std::imag(c), 0.5);

   }
};
TTS_CASE_WITH("Check from_polar simd",
              tts::bunch<kyosu::simd_real_types>,
              tts::randoms(0, +10),
              tts::randoms(-4, +4))
  <typename T>(T const& a0, T const& a1)
{

  using eve::rad;
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto [ra, ia] = kyosu::from_polar(a0[i], a1[i]);
    TTS_ULP_EQUAL(ra, a0[i]*eve::cos(a1[i]), 0.5);
    TTS_ULP_EQUAL(ia, a0[i]*eve::sin(a1[i]), 0.5);
   }
};
