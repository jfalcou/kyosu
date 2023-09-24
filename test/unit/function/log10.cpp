//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::exp over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  auto lr = kyosu::log10(r);
  auto lc = kyosu::log10(c);
  auto lq = kyosu::log10(q);
  TTS_RELATIVE_EQUAL(kyosu::exp10(lr), kyosu::complex(r), 1e-5);
  TTS_RELATIVE_EQUAL(kyosu::exp10(lc), c, 1e-5);
  TTS_RELATIVE_EQUAL(kyosu::exp10(lq), q, 1e-5);
};
