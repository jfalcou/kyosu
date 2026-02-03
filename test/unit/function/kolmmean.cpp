//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH("Check kyosu::kolmmean over real", kyosu::real_types, tts::randoms(0, 10), tts::randoms(0, 10)

)
<typename T>(T r0, T r1)
{
  // quadratic mean
  auto f = [](auto x) { return kyosu::sqr(x); };
  auto g = [](auto x) { return eve::sqrt(x); };
  auto pr = tts::prec<T>(1.0e-1, 1.0e-6);
  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, r0), r0, pr);
  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, r0, r1), eve::hypot(r0, r1) / eve::sqrt_2(eve::as(r0)), pr);
  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, r0, r1, r1), eve::hypot(r0, r1, r1) / eve::sqrt_3(eve::as(r0)), pr);
};

TTS_CASE_WITH("Check kyosu::kolmmean over complex",
              kyosu::real_types,
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10),
              tts::randoms(-10, 10)

)
<typename T>(T r0, T i0, T r1, T i1)
{
  auto pr = tts::prec<T>(1.0e-1, 1.0e-6);
  auto c0 = kyosu::complex(r0, i0);
  auto c1 = kyosu::complex(r1, i1);
  auto f = [](auto x) { return kyosu::sqr(x); };
  auto g = [](auto x) { return kyosu::sqrt(x); };
  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, c0), c0, pr);

  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, c0, c1), g(f(c0) + f(c1)) / eve::sqrt_2(eve::as(r0)), pr);
  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, c0, c1, r1), g(f(c0) + f(c1) + f(r1)) / eve::sqrt_3(eve::as(r0)), pr);
  TTS_RELATIVE_EQUAL(kyosu::kolmmean(f, g, r0, c1, r1), g(f(r0) + f(c1) + f(r1)) / eve::sqrt_3(eve::as(r0)), pr);
};
