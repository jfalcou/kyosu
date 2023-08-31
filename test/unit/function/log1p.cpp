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
              , tts::generate ( tts::between(-10,10), tts::between(-10,10)
                              , tts::between(-10,10), tts::between(-10,10)
                              )
              )
<typename T>(T a0, T a1, T a2, T a3)
{
  using ce_t = kyosu::as_complex_t<T>;
  using qe_t = kyosu::as_quaternion_t<T>;

  auto r  = T(a0);
  auto c  = ce_t(a0,a1);
  auto q  = qe_t(a0,a1,a2,a3);

//   auto lr = kyosu::log1p(r);
//   auto lc = kyosu::log1p(c);
//   auto lq = kyosu::log1p(q);

//   TTS_RELATIVE_EQUAL(kyosu::expm1(lr), kyosu::to_complex(r), 1e-5);
//   TTS_RELATIVE_EQUAL(kyosu::expm1(lc), c, 1e-5);
//   TTS_RELATIVE_EQUAL(kyosu::expm1(lq), q, 1e-5);

  TTS_RELATIVE_EQUAL( kyosu::log1p(r), kyosu::log(kyosu::inc(r)), 1.0e-6);
  TTS_RELATIVE_EQUAL( kyosu::log1p(c), kyosu::log(kyosu::inc(c)), 1.0e-6);
  TTS_RELATIVE_EQUAL( kyosu::log1p(q), kyosu::log(kyosu::inc(q)), 1.0e-6);
};
