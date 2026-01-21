//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::exp over cayley_dickson"
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

  auto rr = eve::log(r);
  auto re = kyosu::log[kyosu::real_only](r);
  TTS_IEEE_EQUAL(re, rr);

  auto lr = kyosu::log(r);
  auto lc = kyosu::log(c);
  auto lq = kyosu::log(q);
  TTS_RELATIVE_EQUAL(kyosu::exp(lr), kyosu::complex(r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp(lc), c, tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::exp(lq), q, 2e-4);

  auto cond = eve::is_ltz(a0);

  TTS_RELATIVE_EQUAL(kyosu::log[cond][kyosu::real_only](r), kyosu::if_else(cond,  eve::log(r), r), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log[cond](r), kyosu::if_else(cond,  kyosu::log(r), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log[cond](c), kyosu::if_else(cond,  kyosu::log(c), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log[cond](q), kyosu::if_else(cond,  kyosu::log(q), q), tts::prec<T>());

  TTS_RELATIVE_EQUAL(kyosu::log[cond](r, 2), kyosu::if_else(cond,  kyosu::log(r, 2), ce_t(r)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log[cond](c, 2), kyosu::if_else(cond,  kyosu::log(c, 2), c), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::log[cond](q, 2), kyosu::if_else(cond,  kyosu::log(q, 2), q), tts::prec<T>());
};
