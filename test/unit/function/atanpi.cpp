//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::atanpi over quaternion"
              , kyosu::simd_real_types
              , tts::generate ( tts::randoms(-1,1), tts::randoms(-1,1)
                              , tts::randoms(-1,1), tts::randoms(-1,1)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::complex_t<T>;
  using qe_t = kyosu::quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

  auto lr = kyosu::atanpi(r);
  auto lc = kyosu::atanpi(c);
  auto lq = kyosu::atanpi(q);
  TTS_RELATIVE_EQUAL(kyosu::tanpi(lr), r, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tanpi(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::tanpi(lq), q, tts::prec<T>());
};
