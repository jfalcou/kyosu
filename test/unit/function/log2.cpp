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

  auto rr = eve::log2(r);
  auto re = kyosu::log2[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::log2(r);
  auto lc = kyosu::log2(c);
  auto lq = kyosu::log2(q);
  TTS_RELATIVE_EQUAL(kyosu::exp2(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp2(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp2(lq), q, 2e-4);


  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::log2[cond][kyosu::real_only](r), kyosu::if_else(cond,  eve::log2(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log2[cond](r), kyosu::if_else(cond,  kyosu::log2(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log2[cond](c), kyosu::if_else(cond,  kyosu::log2(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log2[cond](q), kyosu::if_else(cond,  kyosu::log2(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::log2[cond](r, 2), kyosu::if_else(cond,  kyosu::log2(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log2[cond](c, 2), kyosu::if_else(cond,  kyosu::log2(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log2[cond](q, 2), kyosu::if_else(cond,  kyosu::log2(q, 2), q), tts::prec<T>());
};
