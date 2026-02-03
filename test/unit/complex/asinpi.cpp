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

TTS_CASE_WITH("Check behavior of asinpi on scalar",
              tts::bunch<kyosu::scalar_real_types>,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  auto inv_pi = eve::inv_pi(eve::as<e_t>());
  for (size_t i = 0; i < a0.size(); ++i)
  {
    auto e = a0[i];
    auto f = a1[i];
    auto z = kyosu::complex(e, f);
    TTS_RELATIVE_EQUAL(kyosu::asinpi(z), inv_pi * kyosu::asin(z), tts::prec<T>());
  }
};

TTS_CASE_WITH("Check behavior of asinpi on wide", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  auto inv_pi = eve::inv_pi(eve::as(a0));
  auto z = kyosu::complex(a0, a1);
  TTS_RELATIVE_EQUAL(kyosu::asinpi(z), inv_pi * kyosu::asin(z), tts::prec<T>());
};
